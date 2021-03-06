/* Provide SSL/TLS functions to ESP32 with Arduino IDE
*
* Adapted from the ssl_client1 example of mbedtls.
*
* Original Copyright (C) 2006-2015, ARM Limited, All Rights Reserved, Apache 2.0 License.
* Additions Copyright (C) 2017 Evandro Luis Copercini, Apache 2.0 License.
*/

#include <lwip/err.h>
#include <lwip/sockets.h>
#include <lwip/sys.h>
#include <lwip/netdb.h>
#include <lwip/api.h>
#include <mbedtls/sha256.h>
#include <mbedtls/oid.h>
#include "wifi_ssl_client.h"
#include "ard_ssl.h"
#include "elog.h"

const char *pers = "tls";

static int _handle_error(int err, const char *file, int line)
{
    if (err == -30848)
    {
        return err;
    }
#ifdef MBEDTLS_ERROR_C
    char error_buf[100];
    mbedtls_strerror(err, error_buf, 100);
    log_e("[%s():%d]: (%d) %s", file, line, err, error_buf);
#else
    log_e("[%s():%d]: code %d", file, line, err);
#endif
    return err;
}

#define handle_error(e) _handle_error(e, __FUNCTION__, __LINE__)

wifi_sslclient_context *wifi_ssl_client_create()
{
    wifi_sslclient_context *sslclient = malloc(sizeof(wifi_sslclient_context));
    if(sslclient != NULL){
        char *rootCA = NULL;
        char *cli_cert = NULL;
        char *cli_key = NULL;
        char *pskIdent = NULL;
        char *psKey = NULL;
    }
    return sslclient;
}

void wifi_ssl_client_destroy(wifi_sslclient_context *ssl_client)
{
    if(ssl_client->rootCA != NULL)
    {
        erpc_free(ssl_client->rootCA);
        ssl_client->rootCA = NULL;
    }
    if(ssl_client->cli_cert != NULL)
    {
        erpc_free(ssl_client->cli_cert);
        ssl_client->cli_cert = NULL;
    }
      if(ssl_client->cli_key != NULL)
    {
        erpc_free(ssl_client->cli_key);
        ssl_client->cli_key = NULL;
    }
      if(ssl_client->pskIdent != NULL)
    {
        erpc_free(ssl_client->pskIdent);
        ssl_client->pskIdent = NULL;
    }
    if(ssl_client->psKey != NULL)
    {
        erpc_free(ssl_client->psKey);
        ssl_client->psKey = NULL;
    }
    free(ssl_client);
}

void wifi_ssl_init(wifi_sslclient_context *ssl_client)
{
    mbedtls_ssl_init(&ssl_client->ssl_ctx);
    mbedtls_ssl_config_init(&ssl_client->ssl_conf);
    mbedtls_ctr_drbg_init(&ssl_client->drbg_ctx);
}

void wifi_ssl_set_socket(wifi_sslclient_context *ssl_client, int socket)
{
    ssl_client->socket = socket;
}
void wifi_ssl_set_timeout(wifi_sslclient_context *ssl_client, unsigned long handshake_timeout)
{
    ssl_client->handshake_timeout = handshake_timeout;
}

int wifi_ssl_get_socket(wifi_sslclient_context *ssl_client)
{
    return ssl_client->socket;
}
unsigned long wifi_ssl_get_timeout(wifi_sslclient_context *ssl_client)
{
    return ssl_client->handshake_timeout;
}

uint32_t wifi_ssl_set_rootCA(wifi_sslclient_context *ssl_client, char *rootCABuff)
{
    if(ssl_client->rootCA != NULL)
    {
        erpc_free(ssl_client->rootCA);
        ssl_client->rootCA = NULL;
    }
    ssl_client->rootCA = rootCABuff;
    return ssl_client->rootCA;
}

uint32_t wifi_ssl_get_rootCA(wifi_sslclient_context *ssl_client)
{
    return ssl_client->rootCA;
}

uint32_t wifi_ssl_set_cliCert(wifi_sslclient_context *ssl_client, char *cli_cert)
{
    if(ssl_client->cli_cert != NULL)
    {
        erpc_free(ssl_client->cli_cert);
        ssl_client->cli_cert = NULL;
    }
    ssl_client->cli_cert = cli_cert;
    return ssl_client->cli_cert;
}

uint32_t wifi_ssl_get_cliCert(wifi_sslclient_context *ssl_client)
{
    return ssl_client->cli_cert;
}

uint32_t wifi_ssl_set_cliKey(wifi_sslclient_context *ssl_client, char *cli_key)
{
    if(ssl_client->cli_key != NULL)
    {
        erpc_free(ssl_client->cli_key);
        ssl_client->cli_key = NULL;
    }
    ssl_client->cli_key = cli_key;
    return ssl_client->cli_key;
}

uint32_t wifi_ssl_get_cliKey(wifi_sslclient_context *ssl_client)
{
    return ssl_client->cli_key;
}

uint32_t wifi_ssl_set_pskIdent(wifi_sslclient_context *ssl_client, char *pskIdent)
{
    if(ssl_client->pskIdent != NULL)
    {
        erpc_free(ssl_client->pskIdent);
        ssl_client->pskIdent = NULL;
    }
    ssl_client->pskIdent = pskIdent;
    return ssl_client->pskIdent;
}

uint32_t wifi_ssl_get_pskIdent(wifi_sslclient_context *ssl_client)
{
    return ssl_client->pskIdent;
}

uint32_t wifi_ssl_set_psKey(wifi_sslclient_context *ssl_client, char *psKey)
{
    if(ssl_client->psKey != NULL)
    {
        erpc_free(ssl_client->psKey);
        ssl_client->psKey = NULL;
    }
    ssl_client->psKey = psKey;
    return ssl_client->psKey;
}

uint32_t wifi_ssl_get_psKey(wifi_sslclient_context *ssl_client)
{
    return ssl_client-> psKey;
}

static void *my_calloc(size_t nelements, size_t elementSize)
{
    size_t size;
    void *ptr = NULL;

    size = nelements * elementSize;
    ptr = pvPortMalloc(size);

    if (ptr)
        memset(ptr, 0, size);

    return ptr;
}

static unsigned int ard_ssl_arc4random(void)
{
    unsigned int res = xTaskGetTickCount();
    static unsigned int seed = 0xDEADB00B;

    seed = ((seed & 0x007F00FF) << 7) ^
           ((seed & 0x0F80FF00) >> 8) ^ // be sure to stir those low bits
           (res << 13) ^ (res >> 9);    // using the clock too!

    return seed;
}

static void get_random_bytes(void *buf, size_t len)
{
    unsigned int ranbuf;
    unsigned int *lp;
    int i, count;
    count = len / sizeof(unsigned int);
    lp = (unsigned int *)buf;

    for (i = 0; i < count; i++)
    {
        lp[i] = ard_ssl_arc4random();
        len -= sizeof(unsigned int);
    }

    if (len > 0)
    {
        ranbuf = ard_ssl_arc4random();
        memcpy(&lp[i], &ranbuf, len);
    }
}

static int my_random(void *p_rng, unsigned char *output, size_t output_len)
{
    p_rng = p_rng;
    get_random_bytes(output, output_len);
    return 0;
}

static int my_verify(void *data, mbedtls_x509_crt *crt, int depth, uint32_t *flags)
{
    char buf[1024];
    ((void)data);

    mbedtls_x509_crt_info(buf, (sizeof(buf) - 1), "", crt);

    log_v("\nVerify requested for (Depth %d):\n", depth);
    log_v("%s", buf);

    if ((*flags) == 0)
        log_v(" This certificate has no flags\n");
    else
    {
        mbedtls_x509_crt_verify_info(buf, sizeof(buf), " ! ", *flags);
        log_v("%s\n", buf);
    }

    return (0);
}

int wifi_start_ssl_client(wifi_sslclient_context *ssl_client, const char *host, uint32_t port, int timeout, const char *rootCABuff, const char *cli_cert, const char *cli_key, const char *pskIdent, const char *psKey)
{
    char buf[512];
    int ret, flags;
    int enable = 1;
    int keep_idle = 30;

    log_v("Starting socket");
    ssl_client->socket = -1;

    ssl_client->socket = lwip_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ssl_client->socket < 0)
    {
        log_e("ERROR opening socket");
        return ssl_client->socket;
    }

    ip_addr_t srv;
    if (netconn_gethostbyname(host, &srv) != ERR_OK)
    {
        return -1;
    }
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = srv.addr;
    serv_addr.sin_port = htons(port);

    if (lwip_connect(ssl_client->socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0)
    {
        if (timeout <= 0)
        {
            timeout = 30000;
        }
        lwip_setsockopt(ssl_client->socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
        lwip_setsockopt(ssl_client->socket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
        lwip_setsockopt(ssl_client->socket, IPPROTO_TCP, TCP_NODELAY, &enable, sizeof(enable));
        lwip_setsockopt(ssl_client->socket, SOL_SOCKET, SO_KEEPALIVE, &enable, sizeof(enable));
        lwip_setsockopt(ssl_client->socket, IPPROTO_TCP, TCP_KEEPIDLE, &keep_idle, sizeof(keep_idle));
    }
    else
    {
        log_v("Connect to Server failed!");
        return -1;
    }

    fcntl(ssl_client->socket, F_SETFL, fcntl(ssl_client->socket, F_GETFL, 0) | O_NONBLOCK);
    mbedtls_platform_set_calloc_free(my_calloc, vPortFree);
    log_v("Seeding the random number generator");
    mbedtls_entropy_init(&ssl_client->entropy_ctx);

    ret = mbedtls_ctr_drbg_seed(&ssl_client->drbg_ctx, mbedtls_entropy_func,
                                &ssl_client->entropy_ctx, NULL, 0);

    mbedtls_ssl_init(&ssl_client->ssl_ctx);
    mbedtls_ssl_config_init(&ssl_client->ssl_conf);

    log_v("Setting up the SSL/TLS structure...");

    if ((ret = mbedtls_ssl_config_defaults(&ssl_client->ssl_conf,
                                           MBEDTLS_SSL_IS_CLIENT,
                                           MBEDTLS_SSL_TRANSPORT_STREAM,
                                           MBEDTLS_SSL_PRESET_DEFAULT)) != 0)
    {
        return handle_error(ret);
    }

    mbedtls_ssl_conf_rng(&ssl_client->ssl_conf, mbedtls_ctr_drbg_random, &ssl_client->drbg_ctx);

    // MBEDTLS_SSL_VERIFY_REQUIRED if a CA certificate is defined on Arduino IDE and
    // MBEDTLS_SSL_VERIFY_NONE if not.

    if (rootCABuff != NULL)
    {
        log_v("Loading CA cert");
        // for (int i = 0; i < strlen(rootCABuff); i++)
        // {
        //     printf("%c", rootCABuff[i]);
        // }
        // printf("");
        mbedtls_x509_crt_init(&ssl_client->ca_cert);
        ret = mbedtls_x509_crt_parse(&ssl_client->ca_cert, (const unsigned char *)rootCABuff, strlen(rootCABuff) + 1);
        if (ret < 0)
        {
            return handle_error(ret);
        }
        mbedtls_ssl_conf_ca_chain(&ssl_client->ssl_conf, &ssl_client->ca_cert, NULL);
        mbedtls_ssl_conf_authmode(&ssl_client->ssl_conf, MBEDTLS_SSL_VERIFY_REQUIRED);
        //mbedtls_ssl_conf_verify(&ssl_client->ssl_ctx, my_verify, NULL );
    }
    else if (pskIdent != NULL && psKey != NULL)
    {
        log_v("Setting up PSK");
        // convert PSK from hex to binary
        if ((strlen(psKey) & 1) != 0 || strlen(psKey) > 2 * MBEDTLS_PSK_MAX_LEN)
        {
            log_e("pre-shared key not valid hex or too long");
            return -1;
        }
        unsigned char psk[MBEDTLS_PSK_MAX_LEN];
        size_t psk_len = strlen(psKey) / 2;
        for (int j = 0; j < strlen(psKey); j += 2)
        {
            char c = psKey[j];
            if (c >= '0' && c <= '9')
                c -= '0';
            else if (c >= 'A' && c <= 'F')
                c -= 'A' - 10;
            else if (c >= 'a' && c <= 'f')
                c -= 'a' - 10;
            else
                return -1;
            psk[j / 2] = c << 4;
            c = psKey[j + 1];
            if (c >= '0' && c <= '9')
                c -= '0';
            else if (c >= 'A' && c <= 'F')
                c -= 'A' - 10;
            else if (c >= 'a' && c <= 'f')
                c -= 'a' - 10;
            else
                return -1;
            psk[j / 2] |= c;
        }
        // set mbedtls config
        ret = mbedtls_ssl_conf_psk(&ssl_client->ssl_conf, psk, psk_len,
                                   (const unsigned char *)pskIdent, strlen(pskIdent));
        if (ret != 0)
        {
            log_e("mbedtls_ssl_conf_psk returned %d", ret);
            return handle_error(ret);
        }
        return ret;
    }
    else
    {
        mbedtls_ssl_conf_authmode(&ssl_client->ssl_conf, MBEDTLS_SSL_VERIFY_NONE);
        log_w("WARNING: Use certificates for a more secure communication!");
    }

    if (cli_cert != NULL && cli_key != NULL)
    {
        mbedtls_x509_crt_init(&ssl_client->client_cert);
        mbedtls_pk_init(&ssl_client->client_key);

        log_v("Loading CRT cert");

        ret = mbedtls_x509_crt_parse(&ssl_client->client_cert, (const unsigned char *)cli_cert, strlen(cli_cert) + 1);
        if (ret < 0)
        {
            return handle_error(ret);
        }

        log_v("Loading private key");
        ret = mbedtls_pk_parse_key(&ssl_client->client_key, (const unsigned char *)cli_key, strlen(cli_key) + 1, NULL, 0);

        if (ret != 0)
        {
            return handle_error(ret);
        }

        mbedtls_ssl_conf_own_cert(&ssl_client->ssl_conf, &ssl_client->client_cert, &ssl_client->client_key);
    }

    //log_v("Setting hostname :%s for TLS session...", host);


    if ((ret = mbedtls_ssl_setup(&ssl_client->ssl_ctx, &ssl_client->ssl_conf)) != 0)
    {
        return handle_error(ret);
    }

    mbedtls_ssl_set_bio(&ssl_client->ssl_ctx, &ssl_client->socket, mbedtls_net_send, mbedtls_net_recv, NULL);

    // Hostname set here should match CN in server certificate
    if ((ret = mbedtls_ssl_set_hostname(&ssl_client->ssl_ctx, host)) != 0)
    {
        printf("wifi_start_ssl_client mbedtls_ssl_set_hostname failed \r\n");
        return handle_error(ret);
    }

    log_v("Performing the SSL/TLS handshake...");
    unsigned long handshake_start_time = millis();
    while ((ret = mbedtls_ssl_handshake(&ssl_client->ssl_ctx)) != 0)
    {
        // if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE)
        // {
        //     return handle_error(ret);
        // }
        // log_v("ssl_client->handshake_timeout:%d", ssl_client->handshake_timeout);
        if ((millis() - handshake_start_time) > ssl_client->handshake_timeout)
            return -1;
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }

    if (cli_cert != NULL && cli_key != NULL)
    {
        log_v("Protocol is %s Ciphersuite is %s", mbedtls_ssl_get_version(&ssl_client->ssl_ctx), mbedtls_ssl_get_ciphersuite(&ssl_client->ssl_ctx));
        if ((ret = mbedtls_ssl_get_record_expansion(&ssl_client->ssl_ctx)) >= 0)
        {
            log_v("Record expansion is %d", ret);
        }
        else
        {
            log_w("Record expansion is unknown (compression)");
        }
    }

    log_v("Verifying peer X.509 certificate...");

    if ((flags = mbedtls_ssl_get_verify_result(&ssl_client->ssl_ctx)) != 0)
    {
        bzero(buf, sizeof(buf));
        mbedtls_x509_crt_verify_info(buf, sizeof(buf), "  ! ", flags);
        log_v("Failed to verify peer certificate! verification info: %s", buf);
        wifi_stop_ssl_socket(ssl_client, rootCABuff, cli_cert, cli_key); //It's not safe continue.
        return handle_error(ret);
    }
    else
    {
        log_v("Certificate verified.");
    }

    if (rootCABuff != NULL)
    {
        mbedtls_x509_crt_free(&ssl_client->ca_cert);
    }

    if (cli_cert != NULL)
    {
        mbedtls_x509_crt_free(&ssl_client->client_cert);
    }

    if (cli_key != NULL)
    {
        mbedtls_pk_free(&ssl_client->client_key);
    }

    return ssl_client->socket;

}

void wifi_stop_ssl_socket(wifi_sslclient_context *ssl_client, const char *rootCABuff, const char *cli_cert, const char *cli_key)
{
    log_v("Cleaning SSL connection.");

    if (ssl_client->socket >= 0)
    {
        close(ssl_client->socket);
        ssl_client->socket = -1;
    }

    mbedtls_ssl_free(&ssl_client->ssl_ctx);
    mbedtls_ssl_config_free(&ssl_client->ssl_conf);
    mbedtls_ctr_drbg_free(&ssl_client->drbg_ctx);
    //mbedtls_entropy_free(&ssl_client->entropy_ctx);
}

int wifi_data_to_read(wifi_sslclient_context *ssl_client)
{
    //log_v("RET: %i",ret);   //for low level debug

    // res = mbedtls_ssl_get_bytes_avail(&ssl_client->ssl_ctx);
    // log_v("ssl_ctx: %d res: %d", &ssl_client->ssl_ctx, res);
    //log_v("RES: %i",res);    //for low level debug
    // if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE && ret < 0)
    // {
    //     return handle_error(ret);
    // }
    int ret = 0;
    uint8_t has_backup_recvtimeout = 0;
    int backup_recv_timeout, recv_timeout;
    socklen_t len;
    int retry = 20;

    // peek for 10ms
    ret = lwip_getsockopt(ssl_client->socket, SOL_SOCKET, SO_RCVTIMEO, &backup_recv_timeout, &len);
    if (ret >= 0)
    {
        recv_timeout = 100;
        ret = lwip_setsockopt(ssl_client->socket, SOL_SOCKET, SO_RCVTIMEO, &recv_timeout, sizeof(recv_timeout));
        if (ret >= 0)
        {
            has_backup_recvtimeout = 1;
        }
    }
    uint8_t dummy;
    memset(&dummy, 0, 1);
    ret = -1;
    while (retry-- && ret < 0)
    {
        ret = mbedtls_ssl_read(&ssl_client->ssl_ctx, &dummy, 0);
        log_v("retry :%d ret", retry, ret);
        delay(10);
    }
    if (ret > 0)
    {
        log_v("%c", dummy);
    }

    if (has_backup_recvtimeout == 1)
    {
        // restore receiving timeout
        lwip_setsockopt(ssl_client->socket, SOL_SOCKET, SO_RCVTIMEO, &backup_recv_timeout, sizeof(recv_timeout));
    }

    return ret;
}

int wifi_send_ssl_data(wifi_sslclient_context *ssl_client, const uint8_t *data, uint16_t len)
{
    log_v("Writing HTTP request..."); //for low level debug
    int ret = -1;

    while ((ret = mbedtls_ssl_write(&ssl_client->ssl_ctx, data, len)) <= 0)
    {
        if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE)
        {
            return handle_error(ret);
        }
    }

    len = ret;
    //log_v("%d bytes written", len);  //for low level debug
    return ret;
}

int wifi_get_ssl_receive(wifi_sslclient_context *ssl_client, uint8_t *data, int length)
{
    //log_v( "Reading HTTP response...");   //for low level debug
    int ret = -1;

    ret = mbedtls_ssl_read(&ssl_client->ssl_ctx, data, length);

    //log_v( "%d bytes read", ret);   //for low level debug
    return ret;
}

static bool parseHexNibble(char pb, uint8_t *res)
{
    if (pb >= '0' && pb <= '9')
    {
        *res = (uint8_t)(pb - '0');
        return true;
    }
    else if (pb >= 'a' && pb <= 'f')
    {
        *res = (uint8_t)(pb - 'a' + 10);
        return true;
    }
    else if (pb >= 'A' && pb <= 'F')
    {
        *res = (uint8_t)(pb - 'A' + 10);
        return true;
    }
    return false;
}

#define str_npos (size_t) - 1
static size_t strfind(const char *str, char chr)
{
    if (str == NULL)
        return str_npos;

    char *res = strchr(str, chr);
    if (res == NULL)
        return str_npos;
    else
        return (size_t)(res - str);
}

// Compare a name from certificate and domain name, return true if they match
static bool matchName(const char *name, const char *domainName)
{
    size_t wildcardPos = strfind(name, '*');
    if (wildcardPos == str_npos)
    {
        // Not a wildcard, expect an exact match
        return strcmp(name, domainName);
    }

    size_t firstDotPos = strfind(name, '.');
    if (wildcardPos > firstDotPos)
    {
        // Wildcard is not part of leftmost component of domain name
        // Do not attempt to match (rfc6125 6.4.3.1)
        return false;
    }
    if (wildcardPos != 0 || firstDotPos != 1)
    {
        // Matching of wildcards such as baz*.example.com and b*z.example.com
        // is optional. Maybe implement this in the future?
        return false;
    }
    size_t domainNameFirstDotPos = strfind(domainName, '.');
    if (domainNameFirstDotPos == str_npos)
    {
        return false;
    }

    return strcmp(domainName + domainNameFirstDotPos, name + firstDotPos);
}

// Verifies certificate provided by the peer to match specified SHA256 fingerprint
int wifi_verify_ssl_fingerprint(wifi_sslclient_context *ssl_client, const char *fp, const char *domain_name)
{
    // Convert hex string to byte array
    uint8_t fingerprint_local[32];
    int len = strlen(fp);
    int pos = 0;
    for (size_t i = 0; i < sizeof(fingerprint_local); ++i)
    {
        while (pos < len && ((fp[pos] == ' ') || (fp[pos] == ':')))
        {
            ++pos;
        }
        if (pos > len - 2)
        {
            log_v("pos:%d len:%d fingerprint too short", pos, len);
            return false;
        }
        uint8_t high, low;
        if (!parseHexNibble(fp[pos], &high) || !parseHexNibble(fp[pos + 1], &low))
        {
            log_v("pos:%d len:%d invalid hex sequence: %c%c", pos, len, fp[pos], fp[pos + 1]);
            return false;
        }
        pos += 2;
        fingerprint_local[i] = low | (high << 4);
    }

    // Get certificate provided by the peer
    const mbedtls_x509_crt *crt = mbedtls_ssl_get_peer_cert(&ssl_client->ssl_ctx);

    if (!crt)
    {
        log_v("could not fetch peer certificate");
        return false;
    }

    // Calculate certificate's SHA256 fingerprint
    uint8_t fingerprint_remote[32];
    mbedtls_sha256_context sha256_ctx;
    mbedtls_sha256_init(&sha256_ctx);
    mbedtls_sha256_starts(&sha256_ctx, false);
    mbedtls_sha256_update(&sha256_ctx, crt->raw.p, crt->raw.len);
    mbedtls_sha256_finish(&sha256_ctx, fingerprint_remote);

    // Check if fingerprints match
    if (memcmp(fingerprint_local, fingerprint_remote, 32))
    {
        log_v("fingerprint doesn't match");
        return false;
    }

    // Additionally check if certificate has domain name if provided
    if (domain_name)
        return wifi_verify_ssl_dn(ssl_client, domain_name);
    else
        return true;
}

// Checks if peer certificate has specified domain in CN or SANs
int wifi_verify_ssl_dn(wifi_sslclient_context *ssl_client, const char *domain_name)
{
    log_v("domain name: '%s'", (domain_name) ? domain_name : "(null)");

    char *domain_name_str = (char *)malloc(strlen(domain_name + 1));
    memcpy(domain_name_str, domain_name, strlen(domain_name) + 1);
    strlwr(domain_name_str);

    // Get certificate provided by the peer
    const mbedtls_x509_crt *crt = mbedtls_ssl_get_peer_cert(&ssl_client->ssl_ctx);

    // Check for domain name in SANs
    const mbedtls_x509_sequence *san = &crt->subject_alt_names;
    while (san != NULL)
    {
        char *san_str = (char *)malloc(san->buf.len);
        memcpy(san_str, san->buf.p, san->buf.len);
        strlwr(san_str);

        if (matchName(san_str, domain_name_str))
        {
            free(san_str);
            free(domain_name_str);
            return true;
        }

        log_v("SAN '%s': no match", san_str);

        // Fetch next SAN
        san = san->next;
        free(san_str);
    }

    // Check for domain name in CN
    const mbedtls_asn1_named_data *common_name = &crt->subject;
    while (common_name != NULL)
    {
        // While iterating through DN objects, check for CN object
        if (!MBEDTLS_OID_CMP(MBEDTLS_OID_AT_CN, &common_name->oid))
        {
            char *common_name_str = (char *)malloc(common_name->val.len);
            memcpy(common_name_str, common_name->val.p, common_name->val.len);
            strlwr(common_name_str);

            if (matchName(common_name_str, domain_name_str))
            {
                free(common_name_str);
                free(domain_name_str);
                return true;
            }
            log_v("CN '%s': not match", common_name_str);
            free(common_name_str);
        }

        // Fetch next DN object
        common_name = common_name->next;
    }

    free(domain_name_str);

    return false;
}
void wifi_ssl_strerror(int errnum, char *buffer, size_t buflen)
{
    mbedtls_strerror(errnum, buffer, buflen);
}