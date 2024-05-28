/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 04:29:37 by aaleksee          #+#    #+#             */
/*   Updated: 2024/03/14 04:29:38 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

t_form	*parser_help(t_form *specs, const char **str)
{
	specs = flags_initialisation(specs);
	while (**str && **str == '%')
	{
		(*str)++;
		if (**str == '%')
		{
			specs->specifier = '%';
			(*str)++;
			return (specs);
		}
	}
	while (**str && !ft_strchr(SPECS, **str))
	{
		if (**str == '#')
			specs->hash = 1;
		if (**str == ' ')
			specs->ws = 1;
		if (**str == '+')
			specs->plus = 1;
		(*str)++;
	}
	specs->specifier = **str;
	(*str)++;
	return (specs);
}

void	ft_printing(t_form *specs, va_list args, int **len)
{
	if (specs->specifier == '%')
		return (ft_putchar('%', len));
	if (specs->specifier == 'c')
		return (ft_putchar(va_arg(args, int), len));
	if (specs->specifier == 's')
		return (ft_putstr(va_arg(args, char *), len));
	if (specs->specifier == 'p')
		return (write_address(va_arg(args, void *), len));
	if (specs->specifier == 'd' || specs->specifier == 'i')
		return (ft_getnbr(va_arg(args, int), len, specs));
	if (specs->specifier == 'u')
		return (ft_put_unsigned_nbr(va_arg(args, unsigned int), len, specs));
	if (specs->specifier == 'x')
		return (ft_conversion(va_arg(args, unsigned int), HEX_L, len, specs));
	if (specs->specifier == 'X')
		return (ft_conversion(va_arg(args, unsigned int), HEX_U, len, specs));
	else
		return ;
}

void	parser_main(const char *str, va_list args, int *len)
{
	t_form	*specs;

	while (*str)
	{
		if (*str == '%')
		{
			specs = (t_form *)malloc(1 * sizeof(t_form));
			if (!specs)
				return ;
			specs = parser_help(specs, &str);
			ft_printing(specs, args, &len);
			free(specs);
		}
		else
		{
			ft_putchar(*str, &len);
			str++;
		}
	}
	return ;
}

int	ft_printf(const char *str, ...)
{
	int		len;
	va_list	args;

	len = 0;
	va_start(args, str);
	parser_main(str, args, &len);
	va_end(args);
	return (len);
}
/*
#include <stdio.h>
int main()
{
	// Test case 1
	int *a = NULL;
	int b = printf("%p\n", a);
	int c = ft_printf("%p\n", a);
	printf("C: %d\nM: %d\n\n", b, c);

	// Test case 2
	int a1 = 42;
	int b1 = printf("%p\n", &a1);
	int c1 = ft_printf("%p\n", &a1);
	printf("C: %d\nM: %d\n\n", b1, c1);

	// Test case 3
	char *a2 = "W3E";
	int b2 = printf("\nW %%%% %s aa %% %s\n", "er", a2);
	int c2 = ft_printf("\nW %%%% %s aa %% %s\n", "er", a2);
	printf("%d %d\n\n", b2, c2);

	// Test case 4
	char *a3 = "WELLLLLllll32d";
	int b3 = printf("W %s aa %s\n", "e", a3);
	int c3 = ft_printf("W %s aa %s\n", "e", a3);
	printf("%d %d\n\n", b3, c3);

	// Test case 5
	int a4 = printf("W %d %s\n", 111, "a");
	int b4 = ft_printf("W %d %s\n", 111, "a");
	printf("%d %d\n\n", a4, b4);

	// Test case 6
	char a5 = '-';
	int b5 = printf("W %c aa %c\n", 'e', a5);
	int c5 = ft_printf("W %c aa %c\n", 'e', a5);
	printf("%d %d\n\n", b5, c5);

	// Test case 7
	int a6 = 255;
	int b6 = printf("W %c aa %X\n", 'e', a6);
	int c6 = ft_printf("W %c aa %X\n", 'e', a6);
	printf("%d %d\n\n", b6, c6);

	// Test case 8
	int a7 = 255;
	int b7 = printf("W %c aa %x\n", 'e', a7);
	int c7 = ft_printf("W %c aa %x\n", 'e', a7);
	printf("%d %d\n\n", b7, c7);

	// Test case 9
	// int *b8 = printf(" NULL %s NULL ", NULL);
	int c8 = ft_printf(" NULL %s NULL ", NULL);
	printf("%d\n\n", c8);

	// Test case 10
	// int b9 = printf(" %p ", 1);
	int c9 = ft_printf(" %p ", 17);
	printf("%d\n\n_____\n", c9);

	// Test case 11
	int b10 = printf(" %u \n", -2);
	int c10 = ft_printf(" %u \n", -2);
	printf("%d %d\n\n", b10, c10);

	// Test case 13
	int b12 = printf(" %x \n", -42);
	int c12 = ft_printf(" %x \n", -42);
	printf("%d %d\n\n", b12, c12);

	// Test case 14
	int b13 = printf(" %#X \n", -42);
	int c13 = ft_printf(" %#X \n", -42);
	printf("%d %d\n\n", b13, c13);

	// flags
	printf("flags\n_____\n");
	// Test case 15
	int b14 = printf(" %+d \n", -42);
	int c14 = ft_printf(" %+d \n", -42);
	printf("%d %d\n\n", b14, c14);

	// Test case 16
	int b15 = printf(" % d \n", 42);
	int c15 = ft_printf(" % d \n", 42);
	printf("%d %d\n\n", b15, c15);

	// Test case 17
	int b16 = printf(" %+d \n", -42);
	int c16 = ft_printf(" %+d \n", -42);
	printf("%d %d\n\n", b16, c16);
}
*/