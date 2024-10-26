/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testMini.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:23:42 by linyao            #+#    #+#             */
/*   Updated: 2024/10/26 13:29:02 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTMINI_H
# define TESTMINI_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <stdint.h>
# include <string.h>
# include <ctype.h>

# define MAX_STACK_SIZE 100

typedef struct
{
	char	items[MAX_STACK_SIZE];
	int		top;
} Stack;

void    initStack(Stack *stack);
bool    push(Stack *stack, char c);
bool    pop(Stack *stack);
char    peek(Stack *stack);
bool    isEmpty(Stack *stack);

#endif