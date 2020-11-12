/*
 * Generated by erpcgen 1.7.4 on Thu Nov 12 10:35:46 2020.
 *
 * AUTOGENERATED - DO NOT EDIT
 */


#if !defined(_rpc_wifi_api_server_h_)
#define _rpc_wifi_api_server_h_

#ifdef __cplusplus
#include "erpc_server.h"
#include "erpc_codec.h"
extern "C"
{
#include "rpc_wifi_api.h"
#include <stdint.h>
#include <stdbool.h>
}

#if 10704 != ERPC_VERSION_NUMBER
#error "The generated shim code version is different to the rest of eRPC code."
#endif


/*!
 * @brief Service subclass for rpc_wifi_drv.
 */
class rpc_wifi_drv_service : public erpc::Service
{
public:
    rpc_wifi_drv_service() : Service(krpc_wifi_drv_service_id) {}

    /*! @brief Call the correct server shim based on method unique ID. */
    virtual erpc_status_t handleInvocation(uint32_t methodId, uint32_t sequence, erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory);

private:
    /*! @brief Server shim for rpc_wifi_connect of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_connect_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_connect_bssid of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_connect_bssid_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_disconnect of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_disconnect_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_is_connected_to_ap of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_is_connected_to_ap_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_is_up of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_is_up_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_is_ready_to_transceive of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_is_ready_to_transceive_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_set_mac_address of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_set_mac_address_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_get_mac_address of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_get_mac_address_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_enable_powersave of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_enable_powersave_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_resume_powersave of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_resume_powersave_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_disable_powersave of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_disable_powersave_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_btcoex_set_bt_on of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_btcoex_set_bt_on_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_btcoex_set_bt_off of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_btcoex_set_bt_off_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_get_associated_client_list of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_get_associated_client_list_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_get_ap_bssid of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_get_ap_bssid_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_get_ap_info of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_get_ap_info_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_set_country of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_set_country_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_get_sta_max_data_rate of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_get_sta_max_data_rate_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_get_rssi of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_get_rssi_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_set_channel of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_set_channel_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_get_channel of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_get_channel_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_change_channel_plan of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_change_channel_plan_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_register_multicast_address of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_register_multicast_address_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_unregister_multicast_address of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_unregister_multicast_address_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_rf_on of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_rf_on_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_rf_off of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_rf_off_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_on of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_on_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_off of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_off_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_set_mode of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_set_mode_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_off_fastly of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_off_fastly_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_set_power_mode of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_set_power_mode_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_set_tdma_param of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_set_tdma_param_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_set_lps_dtim of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_set_lps_dtim_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_get_lps_dtim of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_get_lps_dtim_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_set_lps_thresh of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_set_lps_thresh_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_set_lps_level of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_set_lps_level_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_set_mfp_support of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_set_mfp_support_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_start_ap of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_start_ap_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_start_ap_with_hidden_ssid of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_start_ap_with_hidden_ssid_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_set_pscan_chan of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_set_pscan_chan_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_get_setting of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_get_setting_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_set_network_mode of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_set_network_mode_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_get_network_mode of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_get_network_mode_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_set_wps_phase of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_set_wps_phase_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_restart_ap of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_restart_ap_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_config_autoreconnect of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_config_autoreconnect_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_set_autoreconnect of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_set_autoreconnect_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_get_autoreconnect of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_get_autoreconnect_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_get_last_error of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_get_last_error_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_add_custom_ie of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_add_custom_ie_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_update_custom_ie of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_update_custom_ie_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_del_custom_ie of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_del_custom_ie_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_set_indicate_mgnt of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_set_indicate_mgnt_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_get_drv_ability of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_get_drv_ability_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_set_channel_plan of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_set_channel_plan_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_get_channel_plan of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_get_channel_plan_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_enable_forwarding of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_enable_forwarding_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_disable_forwarding of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_disable_forwarding_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_set_ch_deauth of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_set_ch_deauth_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_get_band_type of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_get_band_type_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_set_tx_pause_data of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_set_tx_pause_data_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_get_reconnect_data of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_get_reconnect_data_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_clear_reconnect_data of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_clear_reconnect_data_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_scan_start of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_scan_start_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_is_scaning of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_is_scaning_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_scan_get_ap_records of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_scan_get_ap_records_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_scan_get_ap_num of rpc_wifi_drv interface. */
    erpc_status_t rpc_wifi_scan_get_ap_num_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);
};

/*!
 * @brief Service subclass for rpc_wifi_tcpip.
 */
class rpc_wifi_tcpip_service : public erpc::Service
{
public:
    rpc_wifi_tcpip_service() : Service(krpc_wifi_tcpip_service_id) {}

    /*! @brief Call the correct server shim based on method unique ID. */
    virtual erpc_status_t handleInvocation(uint32_t methodId, uint32_t sequence, erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory);

private:
    /*! @brief Server shim for rpc_tcpip_adapter_init of rpc_wifi_tcpip interface. */
    erpc_status_t rpc_tcpip_adapter_init_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_tcpip_adapter_sta_start of rpc_wifi_tcpip interface. */
    erpc_status_t rpc_tcpip_adapter_sta_start_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_tcpip_adapter_ap_start of rpc_wifi_tcpip interface. */
    erpc_status_t rpc_tcpip_adapter_ap_start_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_tcpip_adapter_stop of rpc_wifi_tcpip interface. */
    erpc_status_t rpc_tcpip_adapter_stop_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_tcpip_adapter_up of rpc_wifi_tcpip interface. */
    erpc_status_t rpc_tcpip_adapter_up_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_tcpip_adapter_down of rpc_wifi_tcpip interface. */
    erpc_status_t rpc_tcpip_adapter_down_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_tcpip_adapter_get_ip_info of rpc_wifi_tcpip interface. */
    erpc_status_t rpc_tcpip_adapter_get_ip_info_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_tcpip_adapter_set_ip_info of rpc_wifi_tcpip interface. */
    erpc_status_t rpc_tcpip_adapter_set_ip_info_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_tcpip_adapter_set_dns_info of rpc_wifi_tcpip interface. */
    erpc_status_t rpc_tcpip_adapter_set_dns_info_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_tcpip_adapter_get_dns_info of rpc_wifi_tcpip interface. */
    erpc_status_t rpc_tcpip_adapter_get_dns_info_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_tcpip_adapter_dhcps_start of rpc_wifi_tcpip interface. */
    erpc_status_t rpc_tcpip_adapter_dhcps_start_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_tcpip_adapter_dhcps_stop of rpc_wifi_tcpip interface. */
    erpc_status_t rpc_tcpip_adapter_dhcps_stop_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_tcpip_adapter_dhcpc_start of rpc_wifi_tcpip interface. */
    erpc_status_t rpc_tcpip_adapter_dhcpc_start_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_tcpip_adapter_dhcpc_stop of rpc_wifi_tcpip interface. */
    erpc_status_t rpc_tcpip_adapter_dhcpc_stop_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_tcpip_adapter_set_hostname of rpc_wifi_tcpip interface. */
    erpc_status_t rpc_tcpip_adapter_set_hostname_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_tcpip_adapter_get_hostname of rpc_wifi_tcpip interface. */
    erpc_status_t rpc_tcpip_adapter_get_hostname_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_tcpip_adapter_get_mac of rpc_wifi_tcpip interface. */
    erpc_status_t rpc_tcpip_adapter_get_mac_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_tcpip_adapter_set_mac of rpc_wifi_tcpip interface. */
    erpc_status_t rpc_tcpip_adapter_set_mac_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);
};

/*!
 * @brief Service subclass for rpc_wifi_lwip.
 */
class rpc_wifi_lwip_service : public erpc::Service
{
public:
    rpc_wifi_lwip_service() : Service(krpc_wifi_lwip_service_id) {}

    /*! @brief Call the correct server shim based on method unique ID. */
    virtual erpc_status_t handleInvocation(uint32_t methodId, uint32_t sequence, erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory);

private:
    /*! @brief Server shim for rpc_lwip_accept of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_accept_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_bind of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_bind_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_shutdown of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_shutdown_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_getpeername of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_getpeername_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_getsockname of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_getsockname_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_getsockopt of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_getsockopt_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_setsockopt of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_setsockopt_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_close of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_close_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_connect of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_connect_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_listen of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_listen_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_available of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_available_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_recv of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_recv_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_read of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_read_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_recvfrom of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_recvfrom_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_send of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_send_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_sendmsg of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_sendmsg_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_sendto of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_sendto_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_socket of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_socket_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_write of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_write_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_writev of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_writev_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_select of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_select_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_ioctl of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_ioctl_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_fcntl of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_fcntl_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_lwip_errno of rpc_wifi_lwip interface. */
    erpc_status_t rpc_lwip_errno_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_netconn_gethostbyname of rpc_wifi_lwip interface. */
    erpc_status_t rpc_netconn_gethostbyname_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_dns_gethostbyname_addrtype of rpc_wifi_lwip interface. */
    erpc_status_t rpc_dns_gethostbyname_addrtype_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);
};

/*!
 * @brief Service subclass for rpc_wifi_mbedtls.
 */
class rpc_wifi_mbedtls_service : public erpc::Service
{
public:
    rpc_wifi_mbedtls_service() : Service(krpc_wifi_mbedtls_service_id) {}

    /*! @brief Call the correct server shim based on method unique ID. */
    virtual erpc_status_t handleInvocation(uint32_t methodId, uint32_t sequence, erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory);

private:
    /*! @brief Server shim for rpc_wifi_ssl_client_create of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_ssl_client_create_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_ssl_client_destroy of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_ssl_client_destroy_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_ssl_init of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_ssl_init_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_ssl_set_socket of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_ssl_set_socket_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_ssl_set_timeout of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_ssl_set_timeout_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_ssl_get_socket of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_ssl_get_socket_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_ssl_get_timeout of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_ssl_get_timeout_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_ssl_set_rootCA of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_ssl_set_rootCA_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_ssl_get_rootCA of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_ssl_get_rootCA_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_ssl_set_cliCert of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_ssl_set_cliCert_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_ssl_get_cliCert of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_ssl_get_cliCert_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_ssl_set_cliKey of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_ssl_set_cliKey_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_ssl_get_cliKey of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_ssl_get_cliKey_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_ssl_set_pskIdent of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_ssl_set_pskIdent_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_ssl_get_pskIdent of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_ssl_get_pskIdent_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_ssl_set_psKey of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_ssl_set_psKey_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_ssl_get_psKey of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_ssl_get_psKey_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_start_ssl_client of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_start_ssl_client_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_stop_ssl_socket of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_stop_ssl_socket_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_data_to_read of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_data_to_read_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_send_ssl_data of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_send_ssl_data_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_get_ssl_receive of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_get_ssl_receive_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_verify_ssl_fingerprint of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_verify_ssl_fingerprint_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_verify_ssl_dn of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_verify_ssl_dn_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for rpc_wifi_ssl_strerror of rpc_wifi_mbedtls interface. */
    erpc_status_t rpc_wifi_ssl_strerror_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);
};

extern "C" {
#else
#include "rpc_wifi_api.h"
#endif // __cplusplus

typedef void * erpc_service_t;

erpc_service_t create_rpc_wifi_drv_service(void);

void destroy_rpc_wifi_drv_service(void);

erpc_service_t create_rpc_wifi_tcpip_service(void);

void destroy_rpc_wifi_tcpip_service(void);

erpc_service_t create_rpc_wifi_lwip_service(void);

void destroy_rpc_wifi_lwip_service(void);

erpc_service_t create_rpc_wifi_mbedtls_service(void);

void destroy_rpc_wifi_mbedtls_service(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _rpc_wifi_api_server_h_
