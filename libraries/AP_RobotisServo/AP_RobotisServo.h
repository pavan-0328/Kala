/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/*
  implementation of Robotis Dynamixel 2.0 protocol for controlling servos
 */

#pragma once

#include <AP_HAL/AP_HAL_Boards.h>

#ifndef AP_ROBOTISSERVO_ENABLED
#define AP_ROBOTISSERVO_ENABLED HAL_PROGRAM_SIZE_LIMIT_KB > 1024
#endif

#if AP_ROBOTISSERVO_ENABLED

#include <AP_HAL/AP_HAL.h>
#include <AP_Param/AP_Param.h>

class AP_RobotisServo {
public:
    AP_RobotisServo();

    /* Do not allow copies */
    CLASS_NO_COPY(AP_RobotisServo);

    static const struct AP_Param::GroupInfo var_info[];
    
    void update();

private:
    AP_HAL::UARTDriver *port{nullptr};
    uint32_t baudrate{0};
    uint32_t us_per_byte{0};
    uint32_t us_gap{0};

    void init(void);
    void detect_servos();

    void add_stuffing(uint8_t *packet);
    void send_packet(uint8_t *txpacket);
    void read_bytes();
    void process_packet(const uint8_t *pkt, uint8_t length);
    void send_command(uint8_t id, uint16_t reg, uint32_t value, uint8_t len);
    void configure_servos(void);

    // auto-detected mask of available servos, from a broadcast ping
    uint32_t servo_mask{0};
    uint8_t detection_count{0};
    uint8_t configured_servos{0};
    bool initialised{false};

    uint8_t pktbuf[64];
    uint8_t pktbuf_ofs{0};

    // servo position limits
    AP_Int32 pos_min;
    AP_Int32 pos_max;

    uint32_t last_send_us{0};
    uint32_t delay_time_us{0};
};

#endif  // AP_ROBOTISSERVO_ENABLED
