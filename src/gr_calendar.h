/**
 * @file gr_calendar.h
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief
 * @version 0.1
 * @date 02/12/2021
 *
 * @copyright Matheus T. dos Santos all rights reserved (c) 2021
 *
 */
#ifndef GREGORIAN_CALENDAR_H
#define GREGORIAN_CALENDAR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <errno.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define GR_MILLENNIUM_BASE_EN 0

#if (GR_MILLENNIUM_BASE_EN == 1)
#define GR_BASE_YEAR 2000
#else
#define GR_BASE_YEAR 1970
#endif

#define GR_CAST_CALENDAR(day_, month_, year_, hour_, minutes_, seconds_, timezone_) \
    ((gr_calendar_t){                                                               \
        .day      = day_,                                                           \
        .month    = month_,                                                         \
        .year     = year_,                                                          \
        .hour     = hour_,                                                          \
        .minutes  = minutes_,                                                       \
        .seconds  = seconds_,                                                       \
        .timezone = timezone_,                                                      \
    })
#define GR_CAST_DAY(day) GR_CAST_CALENDAR(day, 0, 0, 0, 0, 0, 0)
#define GR_CAST_MONTH(month) GR_CAST_CALENDAR(0, month, 0, 0, 0, 0, 0)
#define GR_CAST_YEAR(year) GR_CAST_CALENDAR(0, 0, year, 0, 0, 0, 0)
#define GR_CAST_HOUR(hour) GR_CAST_CALENDAR(0, 0, 0, hour, 0, 0, 0)
#define GR_CAST_MINUTE(minute) GR_CAST_CALENDAR(0, 0, 0, 0, minutes, 0, 0)
#define GR_CAST_SECOND(second) GR_CAST_CALENDAR(0, 0, 0, 0, 0, seconds, 0)
#define GR_CAST_TIMEZONE(timezone) GR_CAST_CALENDAR(0, 0, 0, 0, 0, 0, timezone)

#define GR_TIMESTAMP_MINUTE 60U
#define GR_TIMESTAMP_HOUR 3600U
#define GR_TIMESTAMP_DAY 86400U
#define GR_TIMESTAMP_WEEK 604800U
#define GR_TIMESTAMP_WORK_WEEK 432000U
#define GR_TIMESTAMP_WORK_MONTH 2592000U
#define GR_TIMESTAMP_YEAR 31536000U
#define GR_TIMESTAMP_LEAP_YEAR 31622400U

#define GR_EXT_YEAR(year) ((year) + GR_BASE_YEAR)
#define GR_IS_YEAR_DIVISIBLE(year, value) ((GR_EXT_YEAR(year) % value) == 0)
#define GR_IS_LEAP_YEAR(year)        \
    (GR_IS_YEAR_DIVISIBLE(year, 400) \
     || (GR_IS_YEAR_DIVISIBLE(4) && !GR_IS_YEAR_DIVISIBLE(100)))

#define GR_CHECK_ORD(value, ...) ((value) & (__VA_ARGS__))

#define GR_IS_OCTOBER(month) (((month) == GR_OCTOBER) || ((month) == GR_HEX_OCTOBER))
#define GR_IS_NOVEMBER(month) (((month) == GR_NOVEMBER) || ((month) == GR_HEX_NOVEMBER))
#define GR_IS_DECEMBER(month) (((month) == GR_DECEMBER) || ((month) == GR_HEX_DECEMBER))

#define GR_MONTH2HEX(month)                                                            \
    ((((month) == GR_OCTOBER) || ((month) == GR_NOVEMBER) || ((month) == GR_DECEMBER)) \
         ? ((month) + 6)                                                               \
         : (month))

#define GR_HEX2MONTH(month)                                       \
    ((((month) == GR_HEX_OCTOBER) || ((month) == GR_HEX_NOVEMBER) \
      || ((month) == GR_HEX_DECEMBER))                            \
         ? ((month) -6)                                           \
         : (month))

#define GR_MONTH2STR(month)                                                                        \
    (((month) == GR_JANUARY)                                                                       \
         ? "January"                                                                               \
         : (((month) == GR_FEBRUARY)                                                               \
                ? "February"                                                                       \
                : (((month) == GR_MARCH)                                                           \
                       ? "March"                                                                   \
                       : (((month) == GR_APRIL)                                                    \
                              ? "April"                                                            \
                              : (((month) == GR_MAY)                                               \
                                     ? "May"                                                       \
                                     : (((month) == GR_JUNE)                                       \
                                            ? "June"                                               \
                                            : (((month) == GR_JULY)                                \
                                                   ? "July"                                        \
                                                   : (((month) == GR_AUGUST)                       \
                                                          ? "August"                               \
                                                          : (((month) == GR_SEPTEMBER)             \
                                                                 ? "September"                     \
                                                                 : (GR_IS_OCTOBER(month)           \
                                                                        ? "October"                \
                                                                        : (GR_IS_NOVEMBER(         \
                                                                               month)              \
                                                                               ? "Novem"           \
                                                                                 "ber"             \
                                                                               : (GR_IS_DECEMBER(  \
                                                                                      month)       \
                                                                                      ? "December" \
                                                                                      : "Unknown"))))))))))))

#define GR_MONTH_ABV(month)                                                                       \
    (((month) == GR_JANUARY)                                                                      \
         ? "Jan"                                                                                  \
         : (((month) == GR_FEBRUARY)                                                              \
                ? "Feb"                                                                           \
                : (((month) == GR_MARCH)                                                          \
                       ? "Mar"                                                                    \
                       : (((month) == GR_APRIL)                                                   \
                              ? "Apr"                                                             \
                              : (((month) == GR_MAY)                                              \
                                     ? "May"                                                      \
                                     : (((month) == GR_JUNE)                                      \
                                            ? "Jun"                                               \
                                            : (((month) == GR_JULY)                               \
                                                   ? "Jul"                                        \
                                                   : (((month) == GR_AUGUST)                      \
                                                          ? "Aug"                                 \
                                                          : (((month) == GR_SEPTEMBER)            \
                                                                 ? "Sep"                          \
                                                                 : (GR_IS_OCTOBER(month)          \
                                                                        ? "Oct"                   \
                                                                        : (GR_IS_NOVEMBER(        \
                                                                               month)             \
                                                                               ? "Nov"            \
                                                                               : (GR_IS_DECEMBER( \
                                                                                      month)      \
                                                                                      ? "Dec"     \
                                                                                      : "Err"))))))))))))

#define GR_WEEKDAY2STR(weekday)                                           \
    (((weekday) == GR_SUNDAY)                                             \
         ? "Sunday"                                                       \
         : (((weekday) == GR_MONDAY)                                      \
                ? "Monday"                                                \
                : (((weekday) == GR_TUESDAY)                              \
                       ? "Tuesday"                                        \
                       : (((weekday) == GR_WEDNESDAY)                     \
                              ? "Wednesday"                               \
                              : (((weekday) == GR_THURSDAY)               \
                                     ? "Thursday"                         \
                                     : (((weekday) == GR_FRIDAY)          \
                                            ? "Friday"                    \
                                            : (((weekday) == GR_SATURDAY) \
                                                   ? "Saturday"           \
                                                   : "Unknown")))))))

#define GR_WEEKDAY_ABV(weekday)                                                   \
    (((weekday) == GR_SUNDAY)                                                     \
         ? "Sun"                                                                  \
         : (((weekday) == GR_MONDAY)                                              \
                ? "Mon"                                                           \
                : (((weekday) == GR_TUESDAY)                                      \
                       ? "Tue"                                                    \
                       : (((weekday) == GR_WEDNESDAY)                             \
                              ? "Wed"                                             \
                              : (((weekday) == GR_THURSDAY)                       \
                                     ? "Thu"                                      \
                                     : (((weekday) == GR_FRIDAY)                  \
                                            ? "Fri"                               \
                                            : (((weekday) == GR_SATURDAY) ? "Sat" \
                                                                          : "Err")))))))

typedef uint8_t gr_day_t;
typedef uint8_t gr_month_t;
typedef uint16_t gr_year_t;

typedef int32_t gr_timestamp_t;
typedef uint8_t gr_time_t;

typedef enum {
    GR_JANUARY = 1,
    GR_FEBRUARY,
    GR_MARCH,
    GR_APRIL,
    GR_MAY,
    GR_JUNE,
    GR_JULY,
    GR_AUGUST,
    GR_SEPTEMBER,
    GR_OCTOBER,
    GR_NOVEMBER,
    GR_DECEMBER,
} gr_dec_month_t;

typedef enum {
    GR_HEX_OCTOBER  = 0x10,
    GR_HEX_NOVEMBER = 0x11,
    GR_HEX_DECEMBER = 0x12,
} gr_hex_month_t;

typedef enum {
    GR_SUNDAY = 1,
    GR_MONDAY,
    GR_TUESDAY,
    GR_WEDNESDAY,
    GR_THURSDAY,
    GR_FRIDAY,
    GR_SATURDAY,
} gr_weekday_t;

typedef enum {
    GR_TZ_1 = 1,
    GR_TZ_2,
    GR_TZ_3,
    GR_TZ_4,
    GR_TZ_5,
    GR_TZ_6,
    GR_TZ_7,
    GR_TZ_8,
    GR_TZ_9,
    GR_TZ_10,
    GR_TZ_11,
    GR_TZ_12,
    GR_TZ_N12 = -12,
    GR_TZ_N11,
    GR_TZ_N10,
    GR_TZ_N9,
    GR_TZ_N8,
    GR_TZ_N7,
    GR_TZ_N6,
    GR_TZ_N5,
    GR_TZ_N4,
    GR_TZ_N3,
    GR_TZ_N2,
    GR_TZ_N1,
    GR_TZ_0 = 0,
} gr_tz_t;

typedef struct {
    gr_day_t day;
    gr_month_t month;
    gr_year_t year;
    gr_time_t hour;
    gr_time_t minutes;
    gr_time_t seconds;
    gr_tz_t timezone;
} gr_calendar_t;

typedef enum {
    GR_IS_EQUALS = 0x01,
    GR_IS_FIRST  = 0x02,
    GR_IS_LATER  = 0x04,
} gr_ord_t;

typedef struct {
    uint32_t day;
    uint32_t month;
    uint32_t year;
    uint32_t hour;
    uint32_t minutes;
    uint32_t seconds;
} gr_large_calendar_t;

int gr_calendar_init(gr_calendar_t *calendar, gr_day_t day, gr_month_t month,
                     gr_year_t year, gr_time_t hour, gr_time_t minutes, gr_time_t seconds,
                     gr_tz_t timezone);
int gr_calendar_forward(gr_calendar_t *calendar, gr_large_calendar_t amount);
int gr_calendar_backward(gr_calendar_t *calendar, gr_large_calendar_t amount);
int gr_calendar2timestamp(gr_calendar_t calendar, gr_timestamp_t *timestamp);
int gr_timestamp2calendar(gr_timestamp_t timestamp, gr_calendar_t *calendar);
int gr_calendar_date_between(gr_calendar_t first, gr_calendar_t later,
                             gr_calendar_t *result);
int gr_calendar_get_ord(gr_calendar_t first, gr_calendar_t second, gr_ord_t *result);
int gr_calendar_days_between(gr_calendar_t first, gr_calendar_t later, uint32_t *days);
int gr_calendar_weekday(gr_calendar_t calendar, gr_weekday_t *weekday);
int gr_calendar_week_of_month(gr_calendar_t calendar, uint8_t *week);

#ifdef __cplusplus
}
#endif

#endif  // GREGORIAN_CALENDAR_H
