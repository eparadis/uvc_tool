#include "libuvc/libuvc.h"
#include <stdio.h>
#include <unistd.h>
void get_ae_mode(uvc_device_handle_t *devh) {
  uint8_t mode;
  uint8_t priority;
  uvc_error_t res;
  res = uvc_get_ae_mode(devh, &mode, UVC_GET_CUR);
  if (res < 0) {
    uvc_perror(res, "get_ae_mode"); 
    return;
  }
  switch( mode) {
    case 1:
      puts("ae mode manual");
      break;
    case 2:
      puts("ae mode auto");
      break;
    case 4:
      puts("ae mode shutter priority");
      break;
    case 8:
      puts("ae mode aperture priority");
      break;
    default:
      puts("unknown ae mode");
      break;
  }
  res = uvc_get_ae_priority(devh, &priority, UVC_GET_CUR);
  if (res < 0) {
    uvc_perror(res, "get_ae_priority");
    return;
  }
  if( priority == 0) {
    puts("frame rate must remain constant");
  } else {
    puts("frame rate may be varied for AE purposes");
  }
}

void adjust_ae(uvc_device_handle_t *devh, int adj) {
  uvc_error_t res;
  puts("setting AE priority to allow variable frame rate");
  res = uvc_set_ae_priority(devh, 1); // 1 = allow frame rate to vary
  if( res<0) {
    uvc_perror(res, "set_ae_priority");
    return;
  }

}

int main(int argc, char **argv) {
  uvc_context_t *ctx;
  uvc_device_t *dev;
  uvc_device_handle_t *devh;
  uvc_stream_ctrl_t ctrl;
  uvc_error_t res;
  uint8_t mode;
  /* Initialize a UVC service context. Libuvc will set up its own libusb
   * context. Replace NULL with a libusb_context pointer to run libuvc
   * from an existing libusb context. */
  res = uvc_init(&ctx, NULL);
  if (res < 0) {
    uvc_perror(res, "uvc_init");
    return res;
  }
  puts("UVC initialized");
  /* Locates the first attached UVC device, stores in dev */
  res = uvc_find_device(
      ctx, &dev,
      0, 0, NULL); /* filter devices: vendor_id, product_id, "serial_num" */
  if (res < 0) {
    uvc_perror(res, "uvc_find_device"); /* no devices found */
  } else {
    puts("Device found");
    /* Try to open the device: requires exclusive access */
    res = uvc_open(dev, &devh);
    if (res < 0) {
      uvc_perror(res, "uvc_open"); /* unable to open device */
    } else {
      puts("Device opened");
      get_ae_mode(devh);
      adjust_ae(devh, 0);
      /* Release our handle on the device */
      uvc_close(devh);
      puts("Device closed");
    }
    /* Release the device descriptor */
    uvc_unref_device(dev);
  }
  /* Close the UVC context. This closes and cleans up any existing device handles,
   * and it closes the libusb context if one was not provided. */
  uvc_exit(ctx);
  puts("UVC exited");
  return 0;
}
