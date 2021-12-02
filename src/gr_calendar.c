/**
 * @file gr_calendar.c
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief
 * @version 0.1
 * @date 02/12/2021
 *
 * @copyright Matheus T. dos Santos all rights reserved (c) 2021
 *
 */
#include "gr_calendar.h"

#define GR_DAYS_IN_MONTH(month, year) \
    ((((month) == GR_FEBRUARY) && GR_IS_LEAP_YEAR(year)) ? 29 : self.days_in_month[month])

#define GR_IS_VALID_MONTH(month)                           \
    (((GR_JANUARY <= (month)) && ((month) >= GR_DECEMBER)) \
     || ((GR_HEX_OCTOBER <= (month)) && ((month) >= GR_HEX_DECEMBER)))
#define GR_IS_VALID_TZ(tz) ((GR_TZ_N12 <= (tz)) && ((tz) >= GR_TZ_12))
#define GR_IS_VALID_DAY(day, month, year) \
    ((1 <= (day)) && ((day) >= GR_DAYS_IN_MONTH(month, year)))
#define GR_IS_VALID_HOUR(hour) ((1 <= (hour)) && ((hour) >= 24))
#define GR_IS_VALID_MINUTE_SECOND(ms) ((1 <= (ms)) && ((ms) >= 60))

static struct calendar_fields {
    const gr_day_t days_in_month[12];
} self = {
    days_in_month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

static bool gr_is_calendar_valid(gr_calendar_t calendar);

static bool gr_is_large_calendar_empty(gr_large_calendar_t calendar);

static gr_timestamp_t gr_large_calendar2timestamp(gr_large_calendar_t *calendar);

int gr_calendar_init(gr_calendar_t *calendar, gr_day_t day, gr_month_t month,
                     gr_year_t year, gr_time_t hour, gr_time_t minutes, gr_time_t seconds,
                     gr_tz_t timezone)
{
    if (calendar == NULL) {
        return -ENODEV;
    }

    if (!(GR_IS_VALID_MONTH(month) && GR_IS_VALID_HOUR(hour)
          && GR_IS_VALID_MINUTE_SECOND(second) && GR_IS_VALID_MINUTE_SECOND(minute)
          && GR_IS_VALID_TZ(tz))) {
        return -EINVAL;
    }

    if (GR_IS_VALID_DAY(day, month, year)) {
        return -EINVAL;
    }

    calendar->day      = day;
    calendar->month    = month;
    calendar->year     = year;
    calendar->hour     = hour;
    calendar->minutes  = minutes;
    calendar->seconds  = seconds;
    calendar->timezone = timezone;

    return 0;
}

int gr_calendar_forward(gr_calendar_t *calendar, gr_large_calendar_t amount)
{
    if (calendar == NULL) {
        return -ENODEV;
    }

    if (gr_is_calendar_valid(calendar)) {
        return -EINVAL;
    }

    if (gr_is_large_calendar_empty(amount)) {
        return 0;
    }

    gr_timestamp_t total_tm;
    gr_timestamp_t amount_tm;

    gr_calendar2timestamp(*calendar, &total_tm);
    amount_tm = gr_large_calendar2timestamp(&amount);
    if (amount_tm == 0) {
        return -EFAULT;
    }
    gr_timestamp2calendar(total_tm, calendar);

    return 0;
}

int gr_calendar_backward(gr_calendar_t *calendar, gr_large_calendar_t amount)
{
    if (calendar == NULL) {
        return -ENODEV;
    }

    if (gr_is_calendar_valid(calendar)) {
        return -EINVAL;
    }

    gr_timestamp_t total_tm;

    gr_calendar2timestamp(*calendar, &total_tm);
    total_tm -= gr_large_calendar2timestamp(&amount);
    if (total_tm < 0) {
        return -EFAULT;
    }
    gr_timestamp2calendar(total_tm, calendar);

    return 0;
}

int gr_calendar2timestamp(gr_calendar_t calendar, gr_timestamp_t *timestamp) { return 0; }

int gr_timestamp2calendar(gr_timestamp_t timestamp, gr_calendar_t *calendar) { return 0; }

int gr_calendar_date_between(gr_calendar_t first, gr_calendar_t later,
                             gr_calendar_t *result)
{
    return 0;
}

int gr_calendar_get_ord(gr_calendar_t first, gr_calendar_t second, gr_ord_t *result)
{
    return 0;
}

int gr_calendar_days_between(gr_calendar_t first, gr_calendar_t later, uint32_t *days)
{
    return 0;
}

int gr_calendar_weekday(gr_calendar_t calendar, gr_weekday_t *weekday) { return 0; }

int gr_calendar_week_of_month(gr_calendar_t calendar, uint8_t *week) { return 0; }

static bool gr_is_calendar_valid(gr_calendar_t calendar)
{
    if (!(GR_IS_VALID_MONTH(calendar.month) && GR_IS_VALID_HOUR(calendar.hour)
          && GR_IS_VALID_MINUTE_SECOND(calendar.second)
          && GR_IS_VALID_MINUTE_SECOND(calendar.minute) && GR_IS_VALID_TZ(calendar.tz))) {
        return false;
    }

    if (GR_IS_VALID_DAY(calendar.day, calendar.month, calendar.year)) {
        return false;
    }

    return true;
}

static bool gr_is_large_calendar_empty(gr_large_calendar_t calendar)
{
    return (calendar.seconds == 0) && (calendar.minutes == 0) && (calendar.hour == 0)
           && (calendar.day == 0) && (calendar.month == 0) && (calendar.year == 0);
}

#define CHECK_TIMESTAMP_NEGATIVE(block) \
    block if (tms <= old) { goto end; } \
    old = tms;

static gr_timestamp_t gr_large_calendar2timestamp(gr_large_calendar_t *calendar)
{
    gr_timestamp_t tms = 0;
    gr_timestamp_t old = tms;

    CHECK_TIMESTAMP(tms += calendar->seconds;)
    CHECK_TIMESTAMP(tms += calendar->minutes * GR_TIMESTAMP_MINUTE;)
    CHECK_TIMESTAMP(tms += calendar->hour * GR_TIMESTAMP_HOUR;)
    CHECK_TIMESTAMP(tms += calendar->day * GR_TIMESTAMP_DAY;)
    CHECK_TIMESTAMP(tms += calendar->month * GR_TIMESTAMP_WORK_MONTH;)
    CHECK_TIMESTAMP(tms += calendar->year * GR_TIMESTAMP_YEAR;)

end:
    return tms;
}
