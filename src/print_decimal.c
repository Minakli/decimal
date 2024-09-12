#include "s21_decimal.h"

void divide_96bit_by_10(unsigned int *high, unsigned int *mid,
                        unsigned int *low, unsigned int *remainder) {
  unsigned long long temp = 0;
  temp = *high;
  *high = (unsigned int)(temp / 10);
  temp = (temp % 10) << 32 | *mid;
  *mid = (unsigned int)(temp / 10);
  temp = (temp % 10) << 32 | *low;
  *low = (unsigned int)(temp / 10);
  *remainder = (unsigned int)(temp % 10);
}

void print_decimal(s21_decimal a, char *buffer, size_t buffer_size) {
  unsigned int high = a.bits[2];
  unsigned int mid = a.bits[1];
  unsigned int low = a.bits[0];
  int scale = get_scale(a.bits[3]);
  bool sign = check_sign(a.bits[3]);
  int pos = 0;
  if (sign) {
    pos += snprintf(buffer + pos, buffer_size - pos, "-");
  }
  while (high != 0 || mid != 0 || low != 0) {
    unsigned int remainder = 0;
    divide_96bit_by_10(&high, &mid, &low, &remainder);
    pos += snprintf(buffer + pos, buffer_size - pos, "%u", remainder);
  }

  if (pos == 0) {
    pos += snprintf(buffer + pos, buffer_size - pos, "0");
  }

  for (int i = 0; i < pos / 2; i++) {
    char temp = buffer[i];
    buffer[i] = buffer[pos - i - 1];
    buffer[pos - i - 1] = temp;
  }

  if (scale > 0) {
    pos += snprintf(buffer + pos, buffer_size - pos, ".");
    for (int i = 0; i < scale; i++) {
      unsigned int remainder = 0;
      divide_96bit_by_10(&high, &mid, &low, &remainder);
      pos += snprintf(buffer + pos, buffer_size - pos, "%u", remainder);
    }
  }
  buffer[pos] = '\0';
}

// int main() {
//     s21_decimal decimal = {{864758201, 547961186, 0, 589824}};  // Без
//     масштаба и знака print_decimal(decimal);

//     return 0;
// }
