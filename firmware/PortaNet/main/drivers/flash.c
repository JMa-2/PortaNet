#include "flash.h"

#include <stdbool.h>
#include "nvs_flash.h"
#include "nvs.h"

static bool inited = false;
static nvs_handle_t handle;

static bool InitFlash(void);
static bool CheckInit(void);

//TODO: be sure to use nvs_commit()


static bool InitFlash(void)
{
    if (inited)
        return true;

    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) 
    {
        nvs_flash_erase();
        err = nvs_flash_init();
    }

    if (err != ESP_OK)
        return false;
    

    err = nvs_open("storage", NVS_READWRITE, &handle);

    if (err == ESP_OK)
        return true;

    return false;
}



static bool CheckInit(void)
{
    if (!inited)
    {
        inited = InitFlash();
    }

    return inited;
}



bool u8ReadFlash(const char *section, uint8_t *buffer)
{
    if (!CheckInit())
        return false;

    esp_err_t err = nvs_get_u8(handle, section, buffer);

    if (err == ESP_OK)
        return true;

    return false;
}



bool u8WriteFlash(const char *section, uint8_t val)
{
    if (!CheckInit())
        return false;

    esp_err_t err = nvs_set_u8(handle, section, val);

    if (err != ESP_OK)
        return false;

    err = nvs_commit(handle);

    if (err == ESP_OK)
        return true;

    return false;
}



bool strReadFlash(const char *section, char *buffer, size_t *len)
{
    if (!CheckInit())
        return false;

    nvs_get_str(handle, section, NULL, len);
    esp_err_t err = nvs_get_str(handle, section, buffer, len);

    if (err == ESP_OK)
        return true;

    return false;
}



bool strWriteFlash(const char *section, char *str)
{
    if (!CheckInit())
        return false;

    esp_err_t err = nvs_set_str(handle, section, str);

    if (err != ESP_OK)
        return false;

    err = nvs_commit(handle);

    if (err == ESP_OK)
        return true;

    return false;
}







