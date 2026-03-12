#include <oeuf.h>
#include <string.h>
#include <malloc.h>

char	*itoa(int n)
{
	char	*res;
	size_t	i;

	if (n == -2147483648)
		return (strdup("-2147483648"));
	if (n == 0)
		return (strdup("0"));
	i = oe_i64_len(n);
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		return (NULL);
	res[i] = 0;
	if (n < 0)
	{
		res[0] = '-';
		n *= -1;
	}
	while (n)
	{
		res[--i] = (n % 10) + '0';
		n /= 10;
	}
	return (res);
}
