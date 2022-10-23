#ifndef PORT_DEFINE_H
#define PORT_DEFINE_H

/* MACROs for SET, RESET or TOGGLE Output port */
//#define GPIO_HIGH(a,b)          a->ODR|=b
//#define GPIO_LOW(a,b)           a->ODR&=~b
//#define GPIO_TOGGLE(a,b)        a->ODR^=b

//pin 1~10
#define RED_LED_PORT GPIOC
#define RED_LED_PIN  GPIO_Pin_5

#define GREEN_LED_PORT GPIOC
#define GREEN_LED_PIN  GPIO_Pin_6

//#define PA0_PORT                GPIOA
//#define PA0_PIN                 GPIO_Pin_0

//#define PA1_PORT                GPIOA
//#define PA1_PIN                 GPIO_Pin_1

#define COM_PORT GPIOA
#define COM_PIN  GPIO_Pin_2

#define KEY_PORT GPIOA
#define KEY_PIN  GPIO_Pin_3

#define OUT_PORT GPIOD
#define OUT_PIN  GPIO_Pin_0

#define MOTOR_PWM_PORT GPIOB
#define MOTOR_PWM_PIN  GPIO_Pin_0

//pin 11~20
#define KNOB_SWITCH_PORT GPIOC
#define KNOB_SWITCH_PIN  GPIO_Pin_4

#define OLED_SCL_PORT GPIOC
#define OLED_SCL_PIN  GPIO_Pin_1

#define OLED_SDA_PORT GPIOC
#define OLED_SDA_PIN  GPIO_Pin_0

#define FLOW_METER_PORT GPIOB
#define FLOW_METER_PIN  GPIO_Pin_7

#define OVER_ZERO_PORT GPIOB
#define OVER_ZERO_PIN  GPIO_Pin_6

#define VENT_PORT GPIOB
#define VENT_PIN  GPIO_Pin_5

#define PUMP_PORT GPIOB
#define PUMP_PIN  GPIO_Pin_4

#define HEAT_PORT GPIOB
#define HEAT_PIN  GPIO_Pin_3

#define PUMP_SELECT_PORT GPIOB
#define PUMP_SELECT_PIN  GPIO_Pin_2

#define NTC_PORT GPIOB
#define NTC_PIN  GPIO_Pin_1

#define PWM_PIN_LOW()                                  \
    do {                                               \
        GPIO_ResetBits(MOTOR_PWM_PORT, MOTOR_PWM_PIN); \
    } while (0)
#define PWM_PIN_HIGH()                               \
    do {                                             \
        GPIO_SetBits(MOTOR_PWM_PORT, MOTOR_PWM_PIN); \
    } while (0)

//PWM
#define VENT_PIN_LOW()                       \
    do {                                     \
        GPIO_ResetBits(VENT_PORT, VENT_PIN); \
    } while (0)
#define VENT_PIN_HIGH()                    \
    do {                                   \
        GPIO_SetBits(VENT_PORT, VENT_PIN); \
    } while (0)

#define PUMP_PIN_LOW()                       \
    do {                                     \
        GPIO_ResetBits(PUMP_PORT, PUMP_PIN); \
    } while (0)
#define PUMP_PIN_HIGH()                    \
    do {                                   \
        GPIO_SetBits(PUMP_PORT, PUMP_PIN); \
    } while (0)

#define HEAT_PIN_LOW()                       \
    do {                                     \
        GPIO_ResetBits(HEAT_PORT, HEAT_PIN); \
    } while (0)
#define HEAT_PIN_HIGH()                    \
    do {                                   \
        GPIO_SetBits(HEAT_PORT, HEAT_PIN); \
    } while (0)

//LED
#define RUN_LED_TOGGLE()                            \
    do {                                            \
        GPIO_ToggleBits(G_T_LED_PORT, G_T_LED_PIN); \
    } while (0)
#define RUN_LED_OFF()                              \
    do {                                           \
        GPIO_ResetBits(G_T_LED_PORT, G_T_LED_PIN); \
    } while (0)
#define RUN_LED_ON()                             \
    do {                                         \
        GPIO_SetBits(G_T_LED_PORT, G_T_LED_PIN); \
    } while (0)

#define RED_LED_OFF()                              \
    do {                                           \
        GPIO_ResetBits(RED_LED_PORT, RED_LED_PIN); \
    } while (0)
#define RED_LED_ON()                             \
    do {                                         \
        GPIO_SetBits(RED_LED_PORT, RED_LED_PIN); \
    } while (0)

#define GREEN_LED_OFF()                                \
    do {                                               \
        GPIO_ResetBits(GREEN_LED_PORT, GREEN_LED_PIN); \
    } while (0)
#define GREEN_LED_ON()                               \
    do {                                             \
        GPIO_SetBits(GREEN_LED_PORT, GREEN_LED_PIN); \
    } while (0)

#endif
