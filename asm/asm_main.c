/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchantse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 19:55:32 by dchantse          #+#    #+#             */
/*   Updated: 2019/05/22 11:42:42 by dchantse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				main(int ac, char **av)
{
	char		*filename;
	char 		**arr;

	g_files = (t_files *)ft_memalloc(sizeof(t_files));
	g_str = (t_strings *)ft_memalloc(sizeof(t_strings));
	g_tkns = NULL;
	g_exec_size = 0;
	g_posit = 0;
	g_new_l = 0;
	if (ac != 2)
		error("Error: incorrect number of files.");
	arr = ft_strsplit(av[1], '.');
	if ((g_files->f_fd = open(av[1], O_DIRECTORY)) > 0)
		error("Error: this is a directory.");
	g_files->f_fd = open(av[1], O_RDONLY);
	filename = get_name(av[1]);
	write_header();
	write_all();
	if (g_new_l == 0)
		error("error");
	if (!(g_files->s_fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0666)))
		error("Unable to create/open file.");
	ft_printf("Writing output program to %s\n", filename);
	write(g_files->s_fd, g_full_line, g_posit);
	free_structs();
	system("leaks asm");
}

void			write_all(void)
{
	char	*line;
	int 	num;
	int		status;

	num = 0;
	while ((status = get_next_line(g_files->f_fd, &line)) > 0 && num != 2)
	{
		if (comment_line(line))
			free(line);
		else if (ft_strstr(line, NAME_CMD_STRING))
			num += write_name(line);
		else if (ft_strstr(line, COMMENT_CMD_STRING))
			num += write_comment(line);
		else if (find_op(line) != 0)
			error("Syntax error in name/comment.");
		else
			free(line);
	}
	if (status <= 0)
		error("Empty file");
	ft_memcpy(g_full_line + g_posit, g_str->name, PROG_NAME_LENGTH);
	g_posit += PROG_NAME_LENGTH;
	put_hex(0, 4);
	read_asm_put_code_size(line);
	ft_memcpy(g_full_line + g_posit, g_str->comment, COMMENT_LENGTH);
	g_posit += COMMENT_LENGTH;
	put_hex(0, 4);
	write_token();
}

void		write_token()
{
	t_oken		*tmp_tkn;

	tmp_tkn = g_tkns;
	while (tmp_tkn != NULL)
	{
		analize_token(tmp_tkn);
		tmp_tkn = tmp_tkn->next;
	}
	put_exec_code();
}

char			*get_name(char *name)
{
	char	*str;
	char	*ext;
	char	*tmp;
	int		e_len;
	int		name_len;

	e_len = (int)ft_strlen(ft_strrchr(name, '.'));
	name_len = (int)ft_strlen(name) - e_len;
	str = ft_strsub(name, 0, name_len);
	ext = ft_strsub(name, name_len + 1, ft_strlen(str));
	if (ft_strcmp(ext, "s") != 0)
		error("Error: incorrect file extension.");
	tmp = str;
	str = ft_strjoin(str, "1.cor");
	free(tmp);
	free(ext);
	return (str);
}
