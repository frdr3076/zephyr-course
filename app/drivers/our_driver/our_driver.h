#ifndef OUR_DRIVER_H_
#define OUR_DRIVER_H_

#include <zephyr/device.h>

#ifdef __cplusplus
extern "C"{ // main is C++ and driver is C
#endif

/*
@brief Increments counter of instance and returns new value.
@param dev Driver instance (our_driver0, our_driver1)
@param count Output: Value of counter after increment
@return 0 if ok.

*/

int our_driver_increment_counter(const struct device *dev, uint32_t *count); //receibes instance and modifies data of it.

#ifdef __cplusplus

}

#endif

#endif /* OUR_DRIVER_H_ */