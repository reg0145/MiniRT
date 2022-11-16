#include "headers/libft.h"
#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>
#include <stdarg.h>

void	malloc_error(void);

int	ft_putadr(long num)
{
	int			len;
	char		*to_print;

	to_print = ft_based_num_pointer(num, 16);
	if (!to_print)
		return (-1);
	ft_putstr_fd("0x", 1);
	ft_putstr_fd(to_print, 1);
	len = 2 + ft_strlen(to_print);
	free(to_print);
	return (len);
}

static char	*ft_uppercase(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	return (str);
}

char	*ft_str_by_type(int type, int value)
{
	if (type == 'd' || type == 'i')
		return (ft_itoa(value));
	else if (type == 'u')
		return (ft_itoa_unsigned(value));
	else if (type == 'x')
		return (ft_based_num(value, 16));
	else if (type == 'X')
		return ft_uppercase(ft_based_num(value, 16));
	return (0);
}

static int	fp1(int type, long value)
{
	char	*result;
	int		len;

	len = 1;
	if (type == 'c')
		ft_putchar_fd(value, 1);
	else
	{
		result = ft_str_by_type(type, value);
		if (!result)
			return (-1);
		len = ft_strlen(result);
		ft_putstr_fd(result, 1);
		free(result);
	}
	return (len);
}

static int	fp2(int type, long value)
{
	int			len;

	if (type == 's')
	{
		if (value == 0)
		{
			ft_putstr_fd("(null)", 1);
			len = ft_strlen("(null)");
		}
		else
		{
			ft_putstr_fd((char *)value, 1);
			len = ft_strlen((const char *)value);	
		}
	}
	else
		len = ft_putadr(value);
	return (len);
}

int	(*fp(int type))(int, long)
{
	if (type == 'c' || type == 'd' || type == 'i')
		return (fp1);
	if (type == 'u' || type == 'x' || type == 'X')
		return (fp1);
	if (type == 's' || type == 'p')
		return (fp2);
	else
		return (0);
}

int	print_by_type(va_list ap, const char *format)
{
	int				type;
	int				len;
	int				temp;

	len = 0;
	while (*format)
	{
		if (*format == '%' && *(++format) != '%')
		{
			type = *format;
			temp = fp(type)(type, va_arg(ap, long));
			if (temp < 0)
				return (-1);
			len += temp;
		}
		else
		{
			ft_putchar_fd(*format, 1);
			len++;
		}
		format++;
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		len;
	va_list	ap;

	va_start(ap, format);
	len = print_by_type(ap, format);
	va_end(ap);
	return (len);
}

// int	main(void)
// {
// 	char	*a;
// 	char	b[10] = "hihello";
// 	int		c;
// 	int		d;

// 	// malloc_error();
// 	c = printf("c=%c\n", 'a');
// 	d = ft_printf("c=%c\n", 'a');
// 	printf("real : %d, my : %d\n\n", c, d);

// 	c = printf("s=%s\n", b);
// 	d = ft_printf("s=%s\n", b);
// 	printf("real : %d, my : %d\n\n", c, d);

	// c = printf("%p %p\n", ULONG_MAX, -ULONG_MAX);
	// d = ft_printf("%p %p\n", ULONG_MAX, -ULONG_MAX);
	// printf("real : %d, my : %d\n\n", c, d);

// 	c = printf("%%=%% %d %d\n", 100, 100);
// 	d = ft_printf("%%=%% %d %d\n", 100, 100);
// 	printf("real : %d, my : %d\n\n", c, d);

// 	c = printf("d=%d %d\n", 2147483647, 100);
// 	d = ft_printf("d=%d %d\n", 2147483647, 100);
// 	printf("real : %d, my : %d\n\n", c, d);

// 	c = printf("i=%i %i\n", 2147483647, 123);
// 	d = ft_printf("i=%i %i\n", 2147483647, 123);
// 	printf("real : %d, my : %d\n\n", c, d);

// 	c = printf("u=%u %x\n", 2147483648, 123);
// 	d = ft_printf("u=%u %x\n", 2147483648, 123);
// 	printf("real : %d, my : %d\n\n", c, d);

// 	c = printf("x=%x\n", 4242);
// 	d = ft_printf("x=%x\n", 4242);
// 	printf("real : %d, my : %d\n\n", c, d);

// 	c = printf("X=%X\n", 4242);
// 	d = ft_printf("X=%X\n", 4242);
// 	printf("real : %d, my : %d\n\n", c, d);
// 	return (0);
// }