#ifndef FT_PRINTF_H
# define FT_PRINTF_H

char	*ft_based_num(int n, int base);
char	*ft_based_num_pointer(long n, int base);
char	*ft_itoa_unsigned(int n);
int		ft_printf(const char *format, ...);

#endif
