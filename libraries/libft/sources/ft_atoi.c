/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alexander <alexander@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/04 16:28:53 by alexander     #+#    #+#                 */
/*   Updated: 2021/04/13 11:15:57 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static int	ft_whtspce(const char *str)
{
	long	i;
	int		whtspce;

	i = 0;
	whtspce = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
			whtspce++;
		else if (str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
			whtspce++;
		else
			break ;
		i++;
	}
	return (whtspce);
}

int	ft_atoi(const char *str)
{
	long	value;
	long	i;
	int		neg;

	i = ft_whtspce(str);
	value = 0;
	neg = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = value * 10;
		value = value + str[i] - '0';
		i++;
	}
	return (value * neg);
}
