/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:59:00 by saraki            #+#    #+#             */
/*   Updated: 2024/05/15 06:52:54 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_test.h"

// Avoid err `more undefined references to `g_signal' follow`
#include <signal.h>
volatile sig_atomic_t	g_signal = 0;

#include <stdio.h>
#include <stdlib.h>
 
int main(void)
{
   error_println("This is err msg");
}