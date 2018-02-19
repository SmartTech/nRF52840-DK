#ifndef _NRF52_UART_H_
#define _NRF52_UART_H_

#include "sdk_common.h"

#include "nrf_drv_common.h"
#include "nrf_gpio.h"

#include "nrf_peripherals.h"
#include "nrf_uarte.h"

#include "sdk_config.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  UART0_INSTANCE_INDEX=0,
  UART1_INSTANCE_INDEX,
  UART_INSTANCE_COUNT
};

#define NRF_UART_HWFC_ENABLED   false

typedef nrf_uarte_hwfc_t       nrf_uart_hwfc_t;
typedef nrf_uarte_parity_t     nrf_uart_parity_t;
typedef nrf_uarte_baudrate_t   nrf_uart_baudrate_t;
typedef nrf_uarte_error_mask_t nrf_uart_error_mask_t;
typedef nrf_uarte_task_t       nrf_uart_task_t;
typedef nrf_uarte_event_t      nrf_uart_event_t;

#define NRF_UART_PSEL_DISCONNECTED 0xFFFFFFFF

/**
 * @brief Structure for the UART driver instance.
 */
typedef struct {
    union
    {
      NRF_UARTE_Type * p_uarte; ///< Pointer to a structure with UARTE registers.
      void * p_reg;
    } reg;
    uint8_t drv_inst_idx;     ///< Driver instance index.
} nrf_drv_uart_t;

#define NRF_DRV_UART_PERIPHERAL(id)  (void *)CONCAT_2(NRF_UARTE, id)

/**
 * @brief Macro for creating an UART driver instance.
 */
#define NRF_DRV_UART_INSTANCE(id)                      \
{                                                      \
  .reg          = {NRF_DRV_UART_PERIPHERAL(id)},       \
  .drv_inst_idx =  CONCAT_3(UART, id, _INSTANCE_INDEX),\
}

/**
 * @brief Types of UART driver events.
 */
typedef enum
{
    NRF_DRV_UART_EVT_TX_DONE, ///< Requested TX transfer completed.
    NRF_DRV_UART_EVT_RX_DONE, ///< Requested RX transfer completed.
    NRF_DRV_UART_EVT_ERROR,   ///< Error reported by UART peripheral.
} nrf_drv_uart_evt_type_t;

/**@brief Structure for UART configuration. */
typedef struct
{
    uint32_t            pseltxd;            ///< TXD pin number.
    uint32_t            pselrxd;            ///< RXD pin number.
    uint32_t            pselcts;            ///< CTS pin number.
    uint32_t            pselrts;            ///< RTS pin number.
    void *              p_context;          ///< Context passed to interrupt handler.
    nrf_uart_hwfc_t     hwfc;               ///< Flow control configuration.
    nrf_uart_parity_t   parity;             ///< Parity configuration.
    nrf_uart_baudrate_t baudrate;           ///< Baudrate.
    uint8_t             interrupt_priority; ///< Interrupt priority.
    bool                use_easy_dma;
} nrf_drv_uart_config_t;

/**@brief UART default configuration. */
#define NRF_DRV_UART_DEFAULT_CONFIG                                                   \
    {                                                                                 \
        .pseltxd            = NRF_UART_PSEL_DISCONNECTED,                             \
        .pselrxd            = NRF_UART_PSEL_DISCONNECTED,                             \
        .pselcts            = NRF_UART_PSEL_DISCONNECTED,                             \
        .pselrts            = NRF_UART_PSEL_DISCONNECTED,                             \
        .p_context          = NULL,                                                   \
        .hwfc               = (nrf_uart_hwfc_t)UART_DEFAULT_CONFIG_HWFC,              \
        .parity             = (nrf_uart_parity_t)UART_DEFAULT_CONFIG_PARITY,          \
        .baudrate           = (nrf_uart_baudrate_t)UART_DEFAULT_CONFIG_BAUDRATE,      \
        .interrupt_priority = UART_DEFAULT_CONFIG_IRQ_PRIORITY,                       \
        .use_easy_dma       = true                                                    \
    }

/**@brief Structure for UART transfer completion event. */
typedef struct
{
    uint8_t * p_data; ///< Pointer to memory used for transfer.
    uint8_t   bytes;  ///< Number of bytes transfered.
} nrf_drv_uart_xfer_evt_t;

/**@brief Structure for UART error event. */
typedef struct
{
    nrf_drv_uart_xfer_evt_t rxtx;      ///< Transfer details includes number of bytes transfered.
    uint32_t                error_mask;///< Mask of error flags that generated the event.
} nrf_drv_uart_error_evt_t;

/**@brief Structure for UART event. */
typedef struct
{
    nrf_drv_uart_evt_type_t type;      ///< Event type.
    union
    {
        nrf_drv_uart_xfer_evt_t  rxtx; ///< Data provided for transfer completion events.
        nrf_drv_uart_error_evt_t error;///< Data provided for error event.
    } data;
} nrf_drv_uart_event_t;

/**
 * @brief UART interrupt event handler.
 *
 * @param[in] p_event    Pointer to event structure. Event is allocated on the stack so it is available
 *                       only within the context of the event handler.
 * @param[in] p_context  Context passed to interrupt handler, set on initialization.
 */
typedef void (*nrf_uart_event_handler_t)(nrf_drv_uart_event_t * p_event, void * p_context);

nrf_drv_uart_t* getInstance(uint8_t instance);

/**
 * @brief Function for initializing the UART driver.
 *
 * This function configures and enables UART. After this function GPIO pins are controlled by UART.
 *
 * @param[in] p_instance    Pointer to the driver instance structure.
 * @param[in] p_config      Initial configuration.
 * @param[in] event_handler Event handler provided by the user. If not provided driver works in
 *                          blocking mode.
 *
 * @retval    NRF_SUCCESS             If initialization was successful.
 * @retval    NRF_ERROR_INVALID_STATE If driver is already initialized.
 */
ret_code_t nrf_drv_uart_init(nrf_drv_uart_t const *        p_instance,
                             nrf_drv_uart_config_t const * p_config,
                             nrf_uart_event_handler_t      event_handler);

void nrf_drv_uart_uninit(nrf_drv_uart_t const * p_instance);

__STATIC_INLINE uint32_t nrf_drv_uart_task_address_get(nrf_drv_uart_t const * p_instance,
                                                       nrf_uart_task_t task);

__STATIC_INLINE uint32_t nrf_drv_uart_event_address_get(nrf_drv_uart_t const * p_instance,
                                                        nrf_uart_event_t event);

/**
 * @brief Function for sending data over UART.
 * @retval    NRF_SUCCESS            If initialization was successful.
 * @retval    NRF_ERROR_BUSY         If driver is already transferring.
 * @retval    NRF_ERROR_FORBIDDEN    If the transfer was aborted from a different context
 *                                   (blocking mode only, also see @ref nrf_drv_uart_rx_disable).
 * @retval    NRF_ERROR_INVALID_ADDR If p_data does not point to RAM buffer (UARTE only).
 */
ret_code_t nrf_drv_uart_tx(nrf_drv_uart_t const * p_instance,
                           uint8_t const * const p_data, uint8_t length);

bool nrf_drv_uart_tx_in_progress(nrf_drv_uart_t const * p_instance);

void nrf_drv_uart_tx_abort(nrf_drv_uart_t const * p_instance);

/**
 * @retval    NRF_SUCCESS            If initialization was successful.
 * @retval    NRF_ERROR_BUSY         If the driver is already receiving
 *                                   (and the secondary buffer has already been set
 *                                    in non-blocking mode).
 * @retval    NRF_ERROR_FORBIDDEN    If the transfer was aborted from a different context
 *                                   (blocking mode only, also see @ref nrf_drv_uart_rx_disable).
 * @retval    NRF_ERROR_INTERNAL     If UART peripheral reported an error.
 * @retval    NRF_ERROR_INVALID_ADDR If p_data does not point to RAM buffer (UARTE only).
 */
ret_code_t nrf_drv_uart_rx(nrf_drv_uart_t const * p_instance,
                           uint8_t * p_data, uint8_t length);

bool nrf_drv_uart_rx_ready(nrf_drv_uart_t const * p_instance);

void nrf_drv_uart_rx_enable(nrf_drv_uart_t const * p_instance);

void nrf_drv_uart_rx_disable(nrf_drv_uart_t const * p_instance);

void nrf_drv_uart_rx_abort(nrf_drv_uart_t const * p_instance);

uint32_t nrf_drv_uart_errorsrc_get(nrf_drv_uart_t const * p_instance);


#ifndef SUPPRESS_INLINE_IMPLEMENTATION
__STATIC_INLINE uint32_t nrf_drv_uart_task_address_get(nrf_drv_uart_t const * p_instance,
                                                       nrf_uart_task_t task)
{
  return nrf_uarte_task_address_get(p_instance->reg.p_uarte, (nrf_uarte_task_t)task);
}

__STATIC_INLINE uint32_t nrf_drv_uart_event_address_get(nrf_drv_uart_t const * p_instance,
                                                        nrf_uart_event_t event)
{
  return nrf_uarte_event_address_get(p_instance->reg.p_uarte, (nrf_uarte_event_t)event);
}
#endif //SUPPRESS_INLINE_IMPLEMENTATION

#ifdef __cplusplus
}
#endif


#endif // _NRF52_UART_H_
