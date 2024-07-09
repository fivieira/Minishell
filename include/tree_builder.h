/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_builder.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:34:22 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/07/09 20:48:39 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_BUILDER_H
# define TREE_BUILDER_H

typedef struct	s_token
{
	char			type;
	char		*content;
	struct s_token	*next;
}	t_token;

typedef struct	s_tokenizer_data
{
	char	*cmd;
	t_token	*tokenlst;
	char	type;
	char	*tokenstr;
}	t_tokenizer_data;

#endif
