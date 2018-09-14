/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 09:40:33 by pstringe          #+#    #+#             */
/*   Updated: 2018/07/25 13:04:15 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

void	test_93()
{
	int a;
	int b;

	ft_putstr("93\n");
	a = printf("A res: @moulitest: %.o %.0o\n", 0, 0);
	b = ft_printf("B res: @moulitest: %.o %.0o\n", 0, 0);
	printf("A ret: %d\n", a);
	printf("B ret: %d\n", b);
	ft_putchar('\n');
}

void	test_94()
{
	int a;
	int b;

	ft_putstr("94\n");
	a = printf("A res: @moulitest: %5.o %5.0o\n", 0, 0);
	b = ft_printf("B res: @moulitest: %5.o %5.0o\n", 0, 0);
	printf("A ret: %d\n", a);
	printf("B ret: %d\n", b);
	ft_putchar('\n');
}

void	test_95()
{
	int a;
	int b;

	ft_putstr("95\n");
	a = printf("A res: @moulitest: %#.o %#.0o\n", 0, 0);
	b = ft_printf("B res: @moulitest: %#.o %#.0o\n", 0, 0);
	printf("A ret: %d\n", a);
	printf("B ret: %d\n", b);
	ft_putchar('\n');
}

void	test_167()
{
	int a;
	int b;

	ft_putstr("167\n");
	a = printf("A res: % 10.5d\n", 4242);
	b = ft_printf("B res: % 10.5d\n", 4242);
	printf("A ret: %d\n", a);
	printf("B ret: %d\n", b);
	ft_putchar('\n');
}

void	test_172()
{
	int a;
	int b;

	ft_putstr("172\n");
	a = printf("A res: %03.2d\n", -1);
	b = ft_printf("B res: %03.2d\n", -1);
	printf("A ret: %d\n", a);
	printf("B ret: %d\n", b);
	ft_putchar('\n');
}

void	p_break_1()
{
	int a;
	int b;

	ft_putstr("p_break_1\n");
	a = printf("A res: % .d\n", -1);
	b = ft_printf("B res: % .d\n", -1);
	printf("A ret: %d\n", a);
	printf("B ret: %d\n", b);
	ft_putchar('\n');
}

void	s_break_1()
{
	int a;
	int b;

	ft_putstr("s_break_1\n");
	a = printf("A res: %3.5s and %4096s\n", "samp1", NULL);
	b = ft_printf("B res: %3.5s and %4096s\n", "samp1", NULL);
	printf("A ret: %d\n", a);
	printf("B ret: %d\n", b);
	ft_putchar('\n');
}

void	w_test_1()
{
	int a;
	int b;

	ft_putstr("s_break_1\n");
	a = printf("A res: %ls\n", L"@@");
	b = ft_printf("B res: %ls\n", L"@@");
	printf("A ret: %d\n", a);
	printf("B ret: %d\n", b);
	ft_putchar('\n');
}

void	test_precision()
{
	test_93();
	test_94();
	test_95();
	test_167();
	test_172();
	p_break_1();
}

void	test_string()
{
	s_break_1();
	w_test_1();
}

int 	main(void)
{
	test_precision();
	test_string();
	return (0);
}
