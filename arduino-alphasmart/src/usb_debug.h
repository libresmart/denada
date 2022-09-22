#ifndef USB_DEBUG_H
#define USB_DEBUG_H

typedef struct
{
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint16_t bcdUSB;
  uint8_t bDeviceClass;
  uint8_t bDeviceSubClass;
  uint8_t bDeviceProtocol;
  uint8_t bMaxPacketSize0;
  uint16_t idVendor;
  uint16_t idProduct;
  uint16_t bcdDevice;
  uint8_t iManufacturer;
  uint8_t iProduct;
  uint8_t iSerialNumber;
  uint8_t bNumConfigurations;
} usb_debug_sDevDesc;

static void usb_status_display(uint8_t usbNum, void *dev)
{
    usb_debug_sDevDesc *device = (usb_debug_sDevDesc *)dev;
    printf("New device detected on USB#%d\n", usbNum);
    printf("desc.bcdUSB             = 0x%04x\n", device->bcdUSB);
    printf("desc.bDeviceClass       = 0x%02x\n", device->bDeviceClass);
    printf("desc.bDeviceSubClass    = 0x%02x\n", device->bDeviceSubClass);
    printf("desc.bDeviceProtocol    = 0x%02x\n", device->bDeviceProtocol);
    printf("desc.bMaxPacketSize0    = 0x%02x\n", device->bMaxPacketSize0);
    printf("desc.idVendor           = 0x%04x\n", device->idVendor);
    printf("desc.idProduct          = 0x%04x\n", device->idProduct);
    printf("desc.bcdDevice          = 0x%04x\n", device->bcdDevice);
    printf("desc.iManufacturer      = 0x%02x\n", device->iManufacturer);
    printf("desc.iProduct           = 0x%02x\n", device->iProduct);
    printf("desc.iSerialNumber      = 0x%02x\n", device->iSerialNumber);
    printf("desc.bNumConfigurations = 0x%02x\n", device->bNumConfigurations);
}

#endif // USB_DEBUG_H