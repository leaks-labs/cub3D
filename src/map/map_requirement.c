/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_requirement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:25:05 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:25:06 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "utils.h"

t_map_exception			ft_check_requirement(t_map *map, char **tmp_map, \
												int32_t fd, size_t i);
static t_dictionary		*ft_set_lexic(t_dictionary	**lexic);
static uint8_t			ft_rule_match(t_dictionary *lexic, char *rule, \
									size_t *index);
static uint8_t			ft_is_match(t_map *map, t_dictionary *lexic, \
									char *line, char *rule);
static t_map_exception	ft_ret_exception(t_dictionary *lexic, char **args, \
											char *line, size_t index);

t_map_exception	ft_check_requirement(t_map *map, char **tmp_map, \
												int32_t fd, size_t i)
{
	static t_dictionary	*lexic;
	size_t				index;
	char				**args;
	char				*line;

	if (0 == i && NULL == ft_set_lexic(&lexic))
		return (REQUIREMENT_ERROR);
	ft_read_line(&line, fd, '\n');
	args = ft_split(line, ' ');
	if (ft_dptrlen(args) != 2 \
		|| ft_rule_match(lexic, args[0], &index) != 0)
	{
		if (NULL == args || ft_is_match(map, lexic, line, args[0]) != 0)
			return (ft_freef("%p%p%P", lexic, line, args), REQUIREMENT_ERROR);
		*tmp_map = ft_strdup(line);
		ft_freef("%p%p%P", lexic, line, args);
		return (NO_MAP_EXCEPTION);
	}
	if (1 == ft_set_args(map, &lexic[index], args[1]))
		return (ft_ret_exception(lexic, args, line, index));
	ft_freef("%p, %P", line, args);
	return (ft_check_requirement(map, tmp_map, fd, ++i));
}

static t_dictionary	*ft_set_lexic(t_dictionary	**lexic)
{
	const t_dictionary	tmp_lexic[N_RULE] = {\
			{NORTH_TEXTURE, MANDATORY, WALL, NORTH, PATH_ERROR}, \
			{SOUTH_TEXTURE, MANDATORY, WALL, SOUTH, PATH_ERROR}, \
			{WEST_TEXTURE, MANDATORY, WALL, WEST, PATH_ERROR}, \
			{EAST_TEXTURE, MANDATORY, WALL, EAST, PATH_ERROR}, \
			{FLOOR_RGB, MANDATORY, FLOOR, 0, RGB_ERROR}, \
			{CEILING_RGB, MANDATORY, CEILING, 0, RGB_ERROR}, \
			{FLOOR_TEXTURE, NOT_MANDATORY, FLOOR, 0, PATH_ERROR}, \
			{CEILING_TEXTURE, NOT_MANDATORY, CEILING, 0, PATH_ERROR}
	};
	size_t				i;

	*lexic = ft_calloc(N_RULE + 1, sizeof(t_dictionary));
	i = 0;
	while (*lexic != NULL && i < N_RULE)
	{
		*(*lexic + i) = tmp_lexic[i];
		++i;
	}
	return (*lexic);
}

static uint8_t	ft_rule_match(t_dictionary *lexic, char *rule, size_t *index)
{
	size_t	i;

	i = 0;
	while (i < N_RULE)
	{
		if (lexic[i].rule_type != MATCH && 0 == ft_strcmp(lexic[i].rule, rule))
		{
			lexic[i].rule_type = MATCH;
			*index = i;
			return (0);
		}
		++i;
	}
	return (1);
}

static uint8_t	ft_is_match(t_map *map, t_dictionary *lexic, char *line, \
								char *rule)
{
	size_t	i;

	i = 0;
	while (i < N_RULE)
	{
		if (lexic[i].rule_type == MANDATORY \
			|| 0 == ft_strcmp(lexic[i].rule, rule))
			return (1);
		++i;
	}
	return (ft_is_valid_map(map, line));
}

static	t_map_exception	ft_ret_exception(t_dictionary *lexic, char **args, \
										char *line, size_t index)
{
	const t_map_exception	e_exp = lexic[index].exception;

	ft_freef("%p, %p, %P", lexic, line, args);
	return (e_exp);
}
