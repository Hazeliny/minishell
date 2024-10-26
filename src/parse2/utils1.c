/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:12:44 by linyao            #+#    #+#             */
/*   Updated: 2024/10/26 13:31:53 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testMini.h"

void	initStack(Stack *stack)
{
	stack->top = -1;
}

bool	push(Stack *stack, char c)
{
	if (stack->top < MAX_STACK_SIZE - 1)
	{
		stack->items[++stack->top] = c;
		return (true);
	}
	return (false);
}

bool	pop(Stack *stack)
{
	if (stack->top >= 0)
	{
		stack->top--;
		return (true);
	}
	return (false);
}

char	peek(Stack *stack)
{
	if (stack->top >= 0)
		return (stack->items[stack->top]);
	return ('\0');
}

bool	isEmpty(Stack *stack)
{
	return (stack->top == -1);
}
