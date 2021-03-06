
/**
*****************************************************************************************
*     Copyright (C) 2020  Seeed Technology Co.,Ltd. All rights reserved.
*****************************************************************************************
   * @file      wifi_api.c
   * @brief     
   * @author    Hongtai.Liu
   * @date      2020-09-18
   * @version   v1.0
   **************************************************************************************
   * @attention
   * <h2><center>&copy; COPYRIGHT 2020 Seeed Technology Co.,Ltd</center></h2>
   **************************************************************************************
  */

#include "elog.h"
#include "wifi_conf.h"
#include "wifi_constants.h"
#include "wifi_structures.h"
#include "rpc_system_header.h"
#include "wifi_callback.h"
#include "wifi_tcpip_adapter.h"
#include "lwip/netdb.h"
#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "wifi_main.h"
#include "wifi_ssl_client.h"
#include <errno.h>

static uint32_t wifi_work_mode = RTW_MODE_NONE;

// Free space allocated inside struct binary_t function implementation
static void free_binary_t_struct(binary_t *data)
{
    if (data->data)
    {
        erpc_free(data->data);
    }
}

//! @name rpc_wifi_drv
//@{
int32_t rpc_wifi_connect(const char * ssid, const char * password, uint32_t security_type, int32_t key_id, uint32_t semaphore)
{
    log_d("called");
    int32_t ret = RTW_ERROR;
    if(password != NULL){
        ret = wifi_connect(ssid, security_type, password, strlen(ssid), strlen(password), key_id, NULL);
    }else{
        ret = wifi_connect(ssid, security_type, NULL, strlen(ssid), 0, key_id, NULL);
    }
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_connect_bssid(const binary_t * bssid, const char * ssid, const char * password, uint32_t security_type, int32_t key_id, uint32_t semaphore)
{
    log_d("called");
    int32_t ret = RTW_ERROR;
    if(password != NULL){
        ret = wifi_connect_bssid(bssid->data, ssid, security_type, password, 6, strlen(ssid), strlen(password), key_id, NULL);
    }else{
        ret = wifi_connect_bssid(bssid->data, ssid, security_type, NULL, 6, strlen(ssid), 0, key_id, NULL);
    }
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_disconnect(void)
{
    log_d("called");
    int32_t ret = RTW_ERROR;
    ret = wifi_disconnect();
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_is_connected_to_ap(void)
{
    log_d("called");
    return wifi_is_connected_to_ap();
}

int32_t rpc_wifi_is_up(uint32_t itf)
{
    log_d("called");
    return wifi_is_up(itf);
}

int32_t rpc_wifi_is_ready_to_transceive(uint32_t itf)
{
    log_d("called");
    return wifi_is_ready_to_transceive(itf);
}

int32_t rpc_wifi_set_mac_address(const binary_t *mac)
{
    log_d("called");
    return wifi_set_mac_address(mac->data);
}

int32_t rpc_wifi_get_mac_address(uint8_t mac[18])
{
    log_d("called");
    return wifi_get_mac_address(mac);
}

int32_t rpc_wifi_enable_powersave(void)
{
    log_d("called");
    return wifi_enable_powersave();
}

int32_t rpc_wifi_resume_powersave(void)
{
    log_d("called");
    return wifi_resume_powersave();
}

int32_t rpc_wifi_disable_powersave(void)
{
    log_d("called");
    return wifi_disable_powersave();
}

void rpc_wifi_btcoex_set_bt_on(void)
{
    log_d("called");
    wifi_btcoex_set_bt_on();
    return;
}

void rpc_wifi_btcoex_set_bt_off(void)
{
    log_d("called");
    wifi_btcoex_set_bt_off();
    return;
}

int32_t rpc_wifi_get_associated_client_list(binary_t *client_list_buffer, uint16_t buffer_length)
{
    log_d("called");
    int32_t ret = 0;
    uint8_t *data = (uint8_t *)erpc_malloc((buffer_length + 1) * sizeof(uint8_t));
    ret = wifi_get_associated_client_list(data, buffer_length);
    client_list_buffer->dataLength = buffer_length;
    client_list_buffer->data = data;
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_get_ap_bssid(uint8_t bssid[6])
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_get_ap_bssid(bssid);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_get_ap_info(binary_t *ap_info, uint32_t *security)
{
    log_d("called");
    int32_t ret = 0;
    rtw_bss_info_t *p_ap_info = (rtw_bss_info_t *)erpc_malloc(sizeof(rtw_bss_info_t));
    ret = wifi_get_ap_info(p_ap_info, security);
    ap_info->data = (uint8_t *)p_ap_info;
    ap_info->dataLength = sizeof(rtw_bss_info_t);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_set_country(uint32_t country_code)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_set_country(country_code);
    log_d("exit");
    return ret;
}
int32_t rpc_wifi_get_sta_max_data_rate(uint8_t *inidata_rate)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_get_sta_max_data_rate(inidata_rate);
    log_d("exit");
    return ret;
}
int32_t rpc_wifi_get_rssi(int32_t *pRSSI)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_get_rssi(pRSSI);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_set_channel(int32_t channel)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_set_channel(channel);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_get_channel(int32_t *channel)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_get_channel(channel);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_change_channel_plan(uint8_t channel_plan)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_change_channel_plan(channel_plan);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_register_multicast_address(const uint8_t mac[6])
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_register_multicast_address(mac);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_unregister_multicast_address(const uint8_t mac[6])
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_unregister_multicast_address(mac);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_rf_on(void)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_rf_on();
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_rf_off(void)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_rf_off();
    if (ret != RTW_ERROR)
    {
        if (wifi_work_mode == RTW_MODE_STA || wifi_work_mode == RTW_MODE_STA_AP)
        {

            wifi_callback_ind(SYSTEM_EVENT_STA_STOP, NULL, 0);
        }
    }
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_on(uint32_t mode)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_on(mode);
    if (ret != RTW_ERROR)
    {
        wifi_work_mode = mode;
        if (mode == RTW_MODE_STA || mode == RTW_MODE_STA_AP)
        {
            wifi_callback_ind(SYSTEM_EVENT_STA_START, NULL, 0);
        }
    }
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_off(void)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_off();
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_set_mode(uint32_t mode)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_set_mode(mode);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_off_fastly(void)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_off_fastly();
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_set_power_mode(uint8_t ips_mode, uint8_t lps_mode)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_set_power_mode(ips_mode, lps_mode);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_set_tdma_param(uint8_t slot_period, uint8_t rfon_period_len_1, uint8_t rfon_period_len_2, uint8_t rfon_period_len_3)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_set_tdma_param(slot_period, rfon_period_len_1, rfon_period_len_2, rfon_period_len_3);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_set_lps_dtim(uint8_t dtim)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_set_lps_dtim(dtim);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_get_lps_dtim(uint8_t *dtim)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_get_lps_dtim(dtim);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_set_lps_thresh(uint8_t mode)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_set_lps_thresh(mode);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_set_lps_level(uint8_t lps_level)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_set_lps_level(lps_level);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_set_mfp_support(uint8_t value)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_set_mfp_support(value);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_start_ap(const char * ssid, const char * password, uint32_t security_type, int32_t channel)
{
    log_d("called");
    int32_t ret = 0;
    int timeout = 20;
    if(password != NULL ){
        ret = wifi_start_ap(ssid, security_type, password, strlen(ssid), strlen(password), channel);
    }else{
        ret = wifi_start_ap(ssid, security_type, NULL, strlen(ssid), 0, channel);
    }
    while (1)
    {
        char essid[33];
        const char * wlan_name = WLAN0_NAME;

        if(wifi_work_mode == RTW_MODE_STA_AP){
            wlan_name = WLAN1_NAME;
        }

        if (wext_get_ssid(wlan_name, ((unsigned char *)essid)) > 0)
        {
            if (strcmp(((const char *)essid), ((const char *)ssid)) == 0)
            {
                log_d("%s started\n", ssid);
                ret = RTW_SUCCESS;
                break;
            }
        }

        if (timeout == 0)
        {
            log_e("Start AP timeout!");
            ret = RTW_TIMEOUT;
            break;
        }

        vTaskDelay(1 * configTICK_RATE_HZ);
        timeout--;
    }
    if (ret == RTW_SUCCESS)
    {
        wifi_callback_ind(SYSTEM_EVENT_AP_START, NULL, 0);
    }
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_start_ap_with_hidden_ssid(const char * ssid, const char * password, uint32_t security_type, int32_t channel)
{
    log_d("called");
    int32_t ret = 0;
    int timeout = 20;
    if(password!= NULL){
        ret = wifi_start_ap_with_hidden_ssid(ssid, security_type, password, strlen(ssid), strlen(password), channel);
    }else{
        ret = wifi_start_ap_with_hidden_ssid(ssid, security_type, NULL, strlen(ssid), 0, channel);
    }
    while (1)
    {
        char essid[33];

        if (wext_get_ssid(WLAN0_NAME, ((unsigned char *)essid)) > 0)
        {
            if (strcmp(((const char *)essid), ((const char *)ssid)) == 0)
            {
                log_d("%s started\n", ssid);
                ret = RTW_SUCCESS;
                break;
            }
        }

        if (timeout == 0)
        {
            log_e("Start AP timeout!");
            ret = RTW_TIMEOUT;
            break;
        }

        vTaskDelay(1 * configTICK_RATE_HZ);
        timeout--;
    }
    if (ret == RTW_SUCCESS)
    {
        wifi_callback_ind(SYSTEM_EVENT_AP_START, NULL, 0);
    }
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_set_pscan_chan(const binary_t *channel_list, uint8_t pscan_config)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_set_pscan_chan(&(channel_list->data), &pscan_config, channel_list->dataLength / 4);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_get_setting(const char *ifname, binary_t *pSetting)
{
    log_d("called");
    int32_t ret = 0;
    rtw_wifi_setting_t *p_pSetting = (rtw_wifi_setting_t *)erpc_malloc(sizeof(rtw_wifi_setting_t));
    ret = wifi_get_setting(ifname, p_pSetting);
    pSetting->data = (uint8_t *)p_pSetting;
    pSetting->dataLength = sizeof(rtw_wifi_setting_t);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_set_network_mode(uint32_t mode)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_set_network_mode(mode);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_get_network_mode(uint32_t *pmode)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_get_network_mode(pmode);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_set_wps_phase(uint8_t is_trigger_wps)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_set_wps_phase(is_trigger_wps);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_restart_ap(const binary_t *ssid, const binary_t *password, uint32_t security_type, int32_t channel)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_restart_ap(ssid->data, security_type, password->data, ssid->dataLength, password->dataLength, channel);
    if (ret != RTW_ERROR)
    {
        wifi_callback_ind(SYSTEM_EVENT_AP_START, NULL, 0);
    }
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_config_autoreconnect(uint8_t mode, uint8_t retry_times, uint16_t timeout)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_config_autoreconnect(mode, retry_times, timeout);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_set_autoreconnect(uint8_t mode)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_set_autoreconnect(mode);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_get_autoreconnect(uint8_t *mode)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_get_autoreconnect(mode);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_get_last_error(void)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_get_last_error();
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_add_custom_ie(const binary_t *cus_ie)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_add_custom_ie(cus_ie->data, cus_ie->dataLength / sizeof(rtw_custom_ie_t));
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_update_custom_ie(const binary_t *cus_ie, int32_t ie_index)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_update_custom_ie(cus_ie->data, ie_index);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_del_custom_ie(void)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_del_custom_ie();
    log_d("exit");
    return ret;
}

void rpc_wifi_set_indicate_mgnt(int32_t enable)
{
    log_d("called");
    wifi_set_indicate_mgnt(enable);
    return;
}

int32_t rpc_wifi_get_drv_ability(uint32_t *ability)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_get_drv_ability(ability);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_set_channel_plan(uint8_t channel_plan)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_set_channel_plan(channel_plan);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_get_channel_plan(uint8_t *channel_plan)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_get_channel_plan(channel_plan);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_enable_forwarding(void)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_enable_forwarding();
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_disable_forwarding(void)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_disable_forwarding();
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_set_ch_deauth(uint8_t enable)
{
    log_d("called");
    int32_t ret = 0;
    ret = wifi_set_ch_deauth(enable);
    log_d("exit");
    return ret;
}

uint8_t rpc_wifi_get_band_type(void)
{
    log_d("called");
    uint8_t ret = 0;
    ret = wifi_get_band_type();
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_set_tx_pause_data(int32_t NewState)
{

    log_d("called");
    int32_t ret = 0;
    ret = wifi_set_tx_pause_data(NewState);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_get_reconnect_data(binary_t *wifi_info)
{
    log_d("called");
    int32_t ret = 0;
    wlan_fast_reconnect_profile_t *_wifi_info = (wlan_fast_reconnect_profile_t *)erpc_malloc(sizeof(wlan_fast_reconnect_profile_t));
    if (!wifi_info)
    {
        wifi_info->dataLength = 1;
        wifi_info->data = &ret;
        log_d("exit");
        return ret;
    }
    ret = wifi_get_reconnect_data(_wifi_info);

    wifi_info->data = _wifi_info;
    wifi_info->dataLength = sizeof(wlan_fast_reconnect_profile_t);

    log_d("exit");
    return ret;
}

int32_t rpc_wifi_clear_reconnect_data(void)
{
    log_d("called");
    return wifi_clear_reconnect_data();
}

int32_t rpc_wifi_scan_start(void)
{
    log_d("called");
    return wifi_scan_start();
}

bool rpc_wifi_is_scaning(void)
{
    log_d("called");
    return wifi_is_scaning();
}

int32_t rpc_wifi_scan_get_ap_records(uint16_t number, binary_t *_scanResult)
{
    log_d("called");
    rtw_scan_result_t *networks = NULL;
    int ret;
    if (number <= WL_NETWORKS_LIST_MAXNUM)
    {
        networks = (rtw_scan_result_t *)erpc_malloc(sizeof(rtw_scan_result_t) * number);
    }
    else
    {
        uint8_t *temp = (uint8_t *)erpc_malloc(1);
        _scanResult->dataLength = 1;
        _scanResult->data = (uint8_t *)temp;
        return -1;
    }

    ret = wifi_scan_get_ap_records(number, networks);
    if (ret == RTW_SUCCESS)
    {
        _scanResult->dataLength = sizeof(rtw_scan_result_t) * number;
        _scanResult->data = (uint8_t *)networks;
    }
    else
    {
        uint8_t *temp = (uint8_t *)erpc_malloc(1);
        _scanResult->dataLength = 1;
        _scanResult->data = (uint8_t *)temp;
    }
    log_d("exit");
    return ret;
}

uint16_t rpc_wifi_scan_get_ap_num(void)
{
    log_d("called");
    return wifi_scan_get_ap_num();
}
//@}

//! @name rpc_wifi_tcpip
//@{
int32_t rpc_tcpip_adapter_init(void)
{
    log_d("called");
    tcpip_adapter_init();
    return ESP_OK;
}

int32_t rpc_tcpip_adapter_sta_start(const binary_t *mac, const binary_t *ip_info)
{
    log_d("called");
    uint8_t *_mac = mac->data;
    tcpip_adapter_ip_info_t *_ip_info = (tcpip_adapter_ip_info_t *)ip_info->data;
    return tcpip_adapter_sta_start(_mac, _ip_info);
}

int32_t rpc_tcpip_adapter_ap_start(const binary_t *mac, const binary_t *ip_info)
{
    log_d("called");
    uint8_t *_mac = mac->data;
    tcpip_adapter_ip_info_t *_ip_info = (tcpip_adapter_ip_info_t *)ip_info->data;
    return tcpip_adapter_ap_start(_mac, _ip_info);
}

int32_t rpc_tcpip_adapter_stop(uint32_t tcpip_if)
{
    log_d("called");
    return tcpip_adapter_stop(tcpip_if);
}

int32_t rpc_tcpip_adapter_up(uint32_t tcpip_if)
{
    log_d("called");
    return tcpip_adapter_up(tcpip_if);
}

int32_t rpc_tcpip_adapter_down(uint32_t tcpip_if)
{
    log_d("called");
    return tcpip_adapter_down(tcpip_if);
}

int32_t rpc_tcpip_adapter_get_ip_info(uint32_t tcpip_if, binary_t *ip_info)
{
    log_d("called");
    esp_err_t ret = ESP_OK;
    tcpip_adapter_ip_info_t *_ip_info = (tcpip_adapter_ip_info_t *)erpc_malloc(sizeof(tcpip_adapter_ip_info_t));
    ret = tcpip_adapter_get_ip_info(tcpip_if, _ip_info);
    ip_info->data = _ip_info;
    ip_info->dataLength = sizeof(tcpip_adapter_ip_info_t);
    log_v("tcpip_if:%d ip_addr:%d netmask:%d, gw:%d", tcpip_if, _ip_info->ip, _ip_info->netmask, _ip_info->gw);
    log_d("exit");
    return ret;
}

int32_t rpc_tcpip_adapter_set_ip_info(uint32_t tcpip_if, const binary_t *ip_info)
{
    log_d("called");
    tcpip_adapter_ip_info_t *_ip_info = (tcpip_adapter_ip_info_t *)ip_info->data;
    return tcpip_adapter_set_ip_info(tcpip_if, _ip_info);
}

int32_t rpc_tcpip_adapter_set_dns_info(uint32_t tcpip_if, uint32_t dns_type, const binary_t *dns)
{
    log_d("called");
    tcpip_adapter_dns_info_t *_dns = (tcpip_adapter_dns_info_t *)dns->data;
    return tcpip_adapter_set_dns_info(tcpip_if, dns_type, _dns);
}

int32_t rpc_tcpip_adapter_get_dns_info(uint32_t tcpip_if, uint32_t dns_type, binary_t *dns)
{
    log_d("called");
    esp_err_t ret = ESP_OK;
    tcpip_adapter_dns_info_t *_dns = (tcpip_adapter_dns_info_t *)erpc_malloc(sizeof(tcpip_adapter_dns_info_t));
    ret = tcpip_adapter_get_dns_info(tcpip_if, dns_type, _dns);
    dns->data = _dns;
    dns->dataLength = sizeof(tcpip_adapter_dns_info_t);
    log_d("exit");
    return ret;
}

int32_t rpc_tcpip_adapter_dhcps_start(uint32_t tcpip_if)
{
    log_d("called");
    return tcpip_adapter_dhcps_start(tcpip_if);
}

int32_t rpc_tcpip_adapter_dhcps_stop(uint32_t tcpip_if)
{
    log_d("called");
    return tcpip_adapter_dhcps_stop(tcpip_if);
}

int32_t rpc_tcpip_adapter_dhcpc_start(uint32_t tcpip_if)
{
    log_d("called");
    return tcpip_adapter_dhcpc_start(tcpip_if);
}

int32_t rpc_tcpip_adapter_dhcpc_stop(uint32_t tcpip_if)
{
    log_d("called");
    return tcpip_adapter_dhcpc_stop(tcpip_if);
}

int32_t rpc_tcpip_adapter_set_hostname(uint32_t tcpip_if, const char *hostname)
{
    log_d("called");
    return tcpip_adapter_set_hostname(tcpip_if, hostname);
}

int32_t rpc_tcpip_adapter_get_hostname(uint32_t tcpip_if, char *hostname)
{
    log_d("called");
    esp_err_t ret = ESP_OK;
    uint8_t *_hostname;
    ret = tcpip_adapter_get_hostname(tcpip_if, &_hostname);
    memset(hostname, 0, 32);
    memcpy(hostname, _hostname, strlen((char *)_hostname) + 1);
    log_d("exit");
    return ret;
}

int32_t rpc_tcpip_adapter_get_mac(uint32_t tcpip_if, binary_t *mac)
{
    log_d("called");
    esp_err_t ret = ESP_OK;
    uint8_t *_mac = erpc_malloc(32 * sizeof(uint8_t));
    ret = tcpip_adapter_get_mac(tcpip_if, _mac);
    mac->data = _mac;
    mac->dataLength = strlen((char *)_mac) + 1;
    log_d("exit");
    return ret;
}

int32_t rpc_tcpip_adapter_set_mac(uint32_t tcpip_if, const binary_t *mac)
{
    log_d("called");
    return tcpip_adapter_set_mac(tcpip_if, mac->data);
}
//@}

//! @name rpc_wifi_lwip
//@{
int32_t rpc_lwip_accept(int32_t s, const binary_t *addr, uint32_t *addrlen)
{
    log_d("called");
    struct sockaddr *_addr = (struct sockaddr *)addr->data;
    return lwip_accept(s, _addr, addrlen);
}

int32_t rpc_lwip_bind(int32_t s, const binary_t *name, uint32_t namelen)
{
    log_d("called");
    struct sockaddr *_name = (struct sockaddr *)name->data;
    return lwip_bind(s, _name, namelen);
}

int32_t rpc_lwip_shutdown(int32_t s, int32_t how)
{
    log_d("called");
    return lwip_shutdown(s, how);
}

int32_t rpc_lwip_getpeername(int32_t s, binary_t *name, uint32_t *namelen)
{
    log_d("called");
    struct sockaddr *_name = (struct sockaddr *)erpc_malloc(sizeof(struct sockaddr));
    memset(_name, 0, sizeof(struct sockaddr));
    int32_t ret = lwip_getpeername(s, _name, namelen);
    name->data = (uint8_t *)_name;
    name->dataLength = sizeof(struct sockaddr);
    log_d("exit");
    return ret;
}

int32_t rpc_lwip_getsockname(int32_t s, binary_t *name, uint32_t *namelen)
{
    log_d("called");
    struct sockaddr *_name = (struct sockaddr *)erpc_malloc(sizeof(struct sockaddr));
    memset(_name, 0, sizeof(struct sockaddr));
    int32_t ret = lwip_getsockname(s, _name, namelen);
    name->data = (uint8_t *)_name;
    name->dataLength = sizeof(struct sockaddr);
    log_d("exit");
    return ret;
}

int32_t rpc_lwip_getsockopt(int32_t s, int32_t level, int32_t optname, const binary_t *in_optval, binary_t *out_optval, uint32_t *optlen)
{
    log_d("called");
    uint8_t *optval = (uint8_t *)erpc_malloc(in_optval->dataLength * sizeof(uint8_t));
    int32_t ret = lwip_getsockopt(s, level, optname, optval, optlen);
    out_optval->data = optval;
    out_optval->dataLength = in_optval->dataLength;
    log_d("exit");
    return ret;
}

int32_t rpc_lwip_setsockopt(int32_t s, int32_t level, int32_t optname, const binary_t *optval, uint32_t optlen)
{
    log_d("called");
    return lwip_setsockopt(s, level, optname, optval->data, optlen);
}

int32_t rpc_lwip_close(int32_t s)
{
    log_d("called");
    return lwip_close(s);
}

int32_t rpc_lwip_connect(int32_t s, const binary_t *name, uint32_t namelen)
{
    log_d("called");
    struct sockaddr *_name = (struct sockaddr *)name->data;
    uint8_t *data = (struct sockaddr *)name->data;
    // for(uint32_t i = 0; i < namelen; i++)
    // {
    //     printf("%02x ", data[i]);
    // }
    // printf("\n\r");
    return lwip_connect(s, _name, namelen);
}

int32_t rpc_lwip_listen(int32_t s, int32_t backlog)
{
    log_d("called");
    return lwip_listen(s, backlog);
}

int32_t rpc_lwip_available(int32_t s)
{
    log_d("called %d", s);
    uint8_t c;
    int ret = 0;
    int try = 20;

    struct sockaddr from;
    socklen_t fromlen;

    uint8_t backup_recvtimeout = 0;
    int backup_recv_timeout, recv_timeout;
    socklen_t len;

    // for MSG_PEEK, we try to peek packets by changing receiving timeout to 10ms
    ret = lwip_getsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &backup_recv_timeout, &len);
    if (ret >= 0)
    {
        recv_timeout = 20;
        ret = lwip_setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &recv_timeout, sizeof(recv_timeout));
        if (ret >= 0)
        {
            backup_recvtimeout = 1;
        }
    }
    ret = -1;
    while (try --&&ret < 0)
    {
        ret = lwip_recv(s, &c, 1, MSG_PEEK);
        log_d("rpc_lwip_available retry %d ret:%d", try, ret);
        delay(20);
    }

    if (backup_recvtimeout == 1)
    {
        // restore receiving timeout
        lwip_setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &backup_recv_timeout, sizeof(recv_timeout));
    }

    log_d("ret %d", ret);

    return ret;
}

int32_t rpc_lwip_recv(int32_t s, binary_t *mem, uint32_t len, int32_t flags, uint32_t timeout)
{
    log_d("called: %d", len);
    uint8_t *_mem = (uint8_t *)erpc_malloc((len + 1) * sizeof(uint8_t));
    int32_t ret = -1;
    ret = lwip_recv(s, _mem, len, flags);
    if (ret > 0)
    {
        mem->data = _mem;
        mem->dataLength = ret;
    }
    else
    {
        mem->data = _mem;
        mem->dataLength = 1;
    }
    log_d("called %d", ret);
    return ret;
}

int32_t rpc_lwip_read(int32_t s, binary_t *mem, uint32_t len, uint32_t timeout)
{
    log_d("called");
    uint8_t *_mem = (uint8_t *)erpc_malloc((len + 1) * sizeof(uint8_t));
    int32_t ret = -1;
    ret = lwip_read(s, _mem, len);
    if (ret > 0)
    {
        mem->data = _mem;
        mem->dataLength = ret;
    }
    else
    {
        mem->data = _mem;
        mem->dataLength = 1;
    }
    return ret;
}

int32_t rpc_lwip_recvfrom(int32_t s, binary_t *mem, uint32_t len, int32_t flags, binary_t *from, uint32_t *fromlen, uint32_t timeout)
{
    log_d("called");
    uint8_t *_mem = (uint8_t *)erpc_malloc((len + 1) * sizeof(uint8_t));
    int32_t ret = -1;
    struct sockaddr * _from = (struct sockaddr *)erpc_malloc(sizeof(struct sockaddr));
    ret = lwip_recvfrom(s, _mem, len, flags, _from, (socklen_t *)fromlen);
    if (ret > 0)
    {
        mem->data = _mem;
        mem->dataLength = ret;
    }
    else
    {
        mem->data = _mem;
        mem->dataLength = 1;
    }
    
    from->data = (uint8_t *)_from;
    from->dataLength = sizeof(struct sockaddr);

    return ret;
}

int32_t rpc_lwip_send(int32_t s, const binary_t *dataptr, int32_t flags)
{
    log_d("rpc_lwip_send called");
    // for (int i = 0; i < dataptr->dataLength; i++)
    // {
    //     printf("%02x ", dataptr->data[i]);
    // }
    // printf("\n\r");
    return lwip_send(s, dataptr->data, dataptr->dataLength, flags);
}

int32_t rpc_lwip_sendmsg(int32_t s, const binary_t *msg_name, const binary_t *msg_iov, const binary_t *msg_control, int32_t msg_flags, int32_t flags)
{
    log_d("called");
    struct msghdr msg;
    msg.msg_name = (void *)msg_name->data;
    msg.msg_namelen = (socklen_t)msg_name->dataLength;
    msg.msg_iov->iov_base = (void *)msg_iov->data;
    msg.msg_iov->iov_len = (void *)msg_iov->dataLength;
    msg.msg_iovlen = (int)msg_iov->dataLength;
    msg.msg_control = (void *)msg_control->data;
    msg.msg_controllen = (socklen_t)msg_control->dataLength;
    msg.msg_flags = (int)msg_flags;
    return lwip_sendmsg(s, &msg, flags);
}

int32_t rpc_lwip_sendto(int32_t s, const binary_t *dataptr, int32_t flags, const binary_t *to, uint32_t tolen)
{
    log_d("called");
    struct sockaddr *_to = (struct sockaddr *)to->data;
    return lwip_sendto(s, dataptr->data, dataptr->dataLength, flags, _to, (socklen_t)tolen);
}

int32_t rpc_lwip_socket(int32_t domain, int32_t l_type, int32_t protocol)
{
    log_d("called");
    return lwip_socket(domain, l_type, protocol);
}

int32_t rpc_lwip_write(int32_t s, const binary_t *dataptr, uint32_t size)
{
    log_d("called");
    return lwip_write(s, dataptr->data, dataptr->dataLength);
}

int32_t rpc_lwip_writev(int32_t s, const binary_t *iov, int32_t iovcnt)
{
    log_d("called");
    struct iovec _iov;
    _iov.iov_base = iov->data;
    _iov.iov_len = iov->dataLength;
    return lwip_writev(s, &_iov, iovcnt);
}

int32_t rpc_lwip_select(int32_t maxfdp1, const binary_t *readset, const binary_t *writeset, const binary_t *exceptset, const binary_t *timeout)
{
    log_d("called");
    fd_set *_readset = NULL;
    fd_set *_writeset = NULL;
    fd_set *_exceptset = NULL;
    struct timeval *_timeval = NULL;
    if (readset != NULL)
        _readset = (fd_set *)readset->data;
    if (writeset != NULL)
        _writeset = (fd_set *)writeset->data;
    if (exceptset != NULL)
        _exceptset = (fd_set *)exceptset->data;
    if (timeout != NULL)
        _timeval = (struct timeval *)timeout->data;
    return lwip_select(maxfdp1, _readset, _writeset, _exceptset, _timeval);
}

int32_t rpc_lwip_ioctl(int32_t s, uint32_t cmd, const binary_t *in_argp, binary_t *out_argp)
{
    log_d("called");
    uint8_t *data = (uint8_t *)erpc_malloc(in_argp->dataLength + 1);
    memcpy(data, in_argp->data, in_argp->dataLength);
    int32_t ret = lwip_ioctl(s, cmd, data);
    out_argp->data = data;
    out_argp->dataLength = in_argp->dataLength;
    log_d("exit");
    return ret;
}

int32_t rpc_lwip_fcntl(int32_t s, int32_t cmd, int32_t val)
{
    log_d("called");
    return lwip_fcntl(s, cmd, val);
}

int32_t rpc_lwip_errno(void)
{
    log_d("called");
    return errno;
}

int8_t rpc_netconn_gethostbyname(const char *name, binary_t *addr)
{
    log_d("called");
    ip_addr_t *ip_addr = (ip_addr_t *)erpc_malloc(sizeof(ip_addr_t));
    err_t ret = netconn_gethostbyname(name, ip_addr);
    addr->data = (uint8_t *)ip_addr;
    addr->dataLength = sizeof(ip_addr_t);
    return (int8_t)ret;
}

// binary_t *rpc_lwip_gethostbyname(const char *name)
// {
//     struct hostent *server_host;
//     server_host = gethostbyname(name);
//     if (!server_host)
//     {
//         return NULL;
//     }

//     uint8_t *data = (uint8_t *)erpc_malloc(sizeof(ip_addr_t));
//     memcpy(data, (void *) server_host->h_addr, sizeof(ip_addr_t));
//     binary_t *res = (binary_t *)erpc_malloc(sizeof(binary_t));

//     res->data = data;
//     res->dataLength = sizeof(binary_t);

//     return res;
// }

// int32_t rpc_lwip_gethostbyname_r(const char *name, binary_t *ret, binary_t *buf, binary_t *result, uint32_t *h_errnop)
// {
//     return -1;
// }

// int32_t rpc_lwip_getaddrinfo(const char *name, const char *servname, const binary_t *hints, binary_t *res)
// {
//     return -1;
// }

extern void wifi_dns_found(const char *name, ip_addr_t *ipaddr, void *callback_arg);

// int8_t rpc_dns_gethostbyname(const char *hostname, binary_t *addr, uint32_t found, const binary_t *callback_arg)
// {
//     log_d("called");
//     ip_addr_t *addr_info = (ip_addr_t *)erpc_malloc(sizeof(ip_addr_t));
//     int ret = 0;
//     if (found != NULL)
//     {
//         ret = dns_gethostbyname(hostname, &addr, wifi_dns_found, callback_arg)
//     }
//     else
//     {
//         ret = dns_gethostbyname(hostname, &addr, NULL, callback_arg);
//     }

//     log_d("exit"); return ret;
// }

int8_t rpc_dns_gethostbyname_addrtype(const char *hostname, binary_t *addr, uint32_t found, const binary_t *callback_arg, uint8_t dns_addrtype)
{
    log_d(" called\n\r");
    ip_addr_t *addr_info = (ip_addr_t *)erpc_malloc(sizeof(ip_addr_t));
    addr->data = (uint8_t *)addr_info;
    addr->dataLength = sizeof(ip_addr_t);

    int ret = 0;
    if (found != 0)
    {
        ret = dns_gethostbyname_addrtype(hostname, addr_info, wifi_dns_found, callback_arg, dns_addrtype);
        if (addr)
        {
            erpc_free(addr);
        }
    }
    else
    {
        ret = dns_gethostbyname_addrtype(hostname, addr_info, NULL, callback_arg, dns_addrtype);
        if (hostname)
        {
            erpc_free(hostname);
        }
        if (addr)
        {
            free_binary_t_struct(addr);
        }
        if (addr)
        {
            erpc_free(addr);
        }
        if (callback_arg)
        {
            free_binary_t_struct(callback_arg);
        }
        if (callback_arg)
        {
            erpc_free(callback_arg);
        }
    }

    log_d("exit");
    return ret;
}

//@}

//! @name rpc_wifi_mbedtls
//@{
uint32_t rpc_wifi_ssl_client_create(void)
{
    log_d("called");
    uint32_t ssl_client = wifi_ssl_client_create();
    return ssl_client;
    log_d("exit");
}
void rpc_wifi_ssl_client_destroy(uint32_t ssl_client)
{
    log_d("called");
    return wifi_ssl_client_destroy(ssl_client);
    log_d("exit");
}

void rpc_wifi_ssl_init(uint32_t ssl_client)
{
    log_d("called");
    wifi_ssl_init(ssl_client);
    log_d("exit");
}

void rpc_wifi_ssl_set_socket(uint32_t *ssl_client, int socket)
{
    log_d("called");
    wifi_ssl_set_socket(ssl_client, socket);
    log_d("exit");
}
void rpc_wifi_ssl_set_timeout(uint32_t *ssl_client, unsigned long handshake_timeout)
{
    log_d("called");
    wifi_ssl_set_timeout(ssl_client, handshake_timeout);
    log_d("exit");
}

int32_t rpc_wifi_ssl_get_socket(uint32_t ssl_client)
{
    log_d("called");
    return wifi_ssl_get_socket(ssl_client);
    log_d("exit");
}

uint32_t rpc_wifi_ssl_get_timeout(uint32_t ssl_client)
{
    log_d("called");
    return wifi_ssl_get_timeout(ssl_client);
    log_d("exit");
}

uint32_t rpc_wifi_ssl_set_rootCA(uint32_t ssl_client, const char * rootCABuff)
{
    log_d("called");
    wifi_ssl_set_rootCA(ssl_client, rootCABuff);
    log_d("exit");
}

uint32_t rpc_wifi_ssl_get_rootCA(uint32_t ssl_client, char * rootCABuff)
{
    log_d("called");
    uint32_t ret = wifi_ssl_get_rootCA(ssl_client);
    if(rootCABuff != NULL)
    {
        strcpy(rootCABuff, (char *)ret);
    }
    log_d("exit");
}

uint32_t rpc_wifi_ssl_set_cliCert(uint32_t ssl_client, const char * cli_cert)
{
    log_d("called");
    wifi_ssl_set_cliCert(ssl_client, cli_cert);
    log_d("exit");
}

uint32_t rpc_wifi_ssl_get_cliCert(uint32_t ssl_client, const char * cli_cert)
{
    log_d("called");
    uint32_t ret = wifi_ssl_get_rootCA(ssl_client);
    if(cli_cert != NULL)
    {
        strcpy(cli_cert, (char *)ret);
    }
    log_d("exit");
}

uint32_t rpc_wifi_ssl_set_cliKey(uint32_t ssl_client, const char * cli_key)
{
    log_d("called");
    wifi_ssl_set_cliKey(ssl_client, cli_key);
    log_d("exit");
}

uint32_t rpc_wifi_ssl_get_cliKey(uint32_t ssl_client, const char * cli_key)
{
    log_d("called");
    uint32_t ret = wifi_ssl_get_cliKey(ssl_client);
    if(cli_key != NULL)
    {
        strcpy(cli_key, (char *)ret);
    }
    log_d("exit");
}

uint32_t rpc_wifi_ssl_set_pskIdent(uint32_t ssl_client, const char * pskIdent)
{
    log_d("called");
    wifi_ssl_set_pskIdent(ssl_client, pskIdent);
    log_d("exit");
}

uint32_t rpc_wifi_ssl_get_pskIdent(uint32_t ssl_client, const char * pskIdent)
{
    log_d("called");
    uint32_t ret = wifi_ssl_get_pskIdent(ssl_client);
    if(pskIdent != NULL)
    {
        strcpy(pskIdent, (char *)ret);
    }
    log_d("exit");
}

uint32_t rpc_wifi_ssl_set_psKey(uint32_t ssl_client, const char * psKey)
{
    log_d("called");
    wifi_ssl_set_psKey(ssl_client, psKey);
    log_d("exit");
}

uint32_t rpc_wifi_ssl_get_psKey(uint32_t ssl_client, const char * psKey)
{
    log_d("called");
    uint32_t ret = wifi_ssl_get_psKey(ssl_client);
    if(psKey != NULL)
    {
        strcpy(psKey, (char *)ret);
    }
    log_d("exit");
}

int32_t rpc_wifi_start_ssl_client(uint32_t ssl_client, const char *host, uint32_t port, int32_t timeout)
{
    log_d("rpc_wifi_start_ssl_client");
    wifi_sslclient_context *_ssl_client = (wifi_sslclient_context *)ssl_client;
    int32_t ret = wifi_start_ssl_client(ssl_client, host, port, timeout, _ssl_client->rootCA, _ssl_client->cli_cert, _ssl_client->cli_key, _ssl_client->pskIdent, _ssl_client->psKey);
    log_d("exit");
    return ret;
}

void rpc_wifi_stop_ssl_socket(uint32_t ssl_client)
{
    log_d("called");
    wifi_stop_ssl_socket(ssl_client, NULL, NULL, NULL);
    log_d("exit");
}

int32_t rpc_wifi_data_to_read(uint32_t ssl_client)
{
    log_d("called");
    int32_t ret = wifi_data_to_read(ssl_client);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_send_ssl_data(uint32_t ssl_client, const binary_t *data, uint16_t len)
{
    log_d("called");
    int32_t ret = wifi_send_ssl_data(ssl_client, data->data, len);
    log_d("exit");
    return ret;
}

int32_t rpc_wifi_get_ssl_receive(uint32_t ssl_client, binary_t *data, int32_t length)
{
    log_d("called");
    uint8_t *buf = erpc_malloc(length + 1);
    int32_t ret = wifi_get_ssl_receive(ssl_client, buf, length);
    data->data = buf;
    if (ret > 0)
    {
        data->dataLength = ret;
    }
    else
    {
        data->dataLength = 1;
    }
    log_d("exit");
    return ret;
}

bool rpc_wifi_verify_ssl_fingerprint(uint32_t ssl_client, const char *fp, const char *domain_name)
{
    log_d("called");
    int32_t ret = wifi_verify_ssl_fingerprint(ssl_client, fp, domain_name);
    log_d("exit");
    return ret;
}

bool rpc_wifi_verify_ssl_dn(uint32_t ssl_client, const char *domain_name)
{
    log_d("called");
    int32_t ret = wifi_verify_ssl_dn(ssl_client, domain_name);
    log_d("exit");
    return ret;
}

void rpc_wifi_ssl_strerror(int32_t errnum, binary_t *buffer, uint32_t buflen)
{
    log_d("called");
    uint8_t *_buffer = erpc_malloc(buflen + 1);
    wifi_ssl_strerror(errnum, _buffer, buflen);
    buffer->data = _buffer;
    buffer->dataLength = buflen;
    log_d("exit");
}

//@}