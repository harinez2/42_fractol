#include "main.h"

size_t	ft_strlen(const char *str)
{
	size_t		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putchars(char *s)
{
	write(1, s, ft_strlen(s));
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;
	int				diff;

	i = 0;
	while (i < n)
	{
		diff = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (diff)
			return (diff);
		if (s1[i] == '\0' || s2[i] == '\0')
			return (diff);
		i++;
	}
	return (0);
}

int	ft_ftoi(char *s, float *num)
{
	float	ret;
	int		i;
	int		neg;
	int		tmp;

	i = 0;
	neg = 1;
	if (s[i] == '-')
		neg = -neg;
	if (s[i] == '-' || s[i] == '+')
		i++;
	ret = 0;
	tmp = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		tmp = 1;
		ret = ret * 10 + s[i++] - '0';
	}
	if (tmp == 0)
		return (0);
	if (s[i] == '.')
		while (s[++i] >= '0' && s[i] <= '9')
			ret = ret + (s[i] - '0') * pow(0.1, tmp++);
	*num = ret * neg;
	return (i);
}

int	ft_hextoi(char *s, int *num)
{
	int		ret;
	int		i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'
		|| s[i] == '\f' || s[i] == '\r' || s[i] == '\v')
		i++;
	ret = 0;
	while (1)
	{
		if (s[i] >= '0' && s[i] <= '9')
			ret = ret * 16 + s[i] - '0';
		else if (s[i] >= 'a' && s[i] <= 'f')
			ret = ret * 16 + s[i] - 'a' + 10;
		else if (s[i] >= 'A' && s[i] <= 'F')
			ret = ret * 16 + s[i] - 'A' + 10;
		else if (s[i] >= '\0')
			break ;
		else
			return (0);
		i++;
	}
	*num = ret;
	return (i);
}
