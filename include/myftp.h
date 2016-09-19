/*
** myftp.h for FTP in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myftp
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon May  2 10:14:53 2016 Victor Gouet
** Last update Fri May 13 15:27:25 2016 Victor Gouet
*/

#ifndef MYFTP_H_
# define MYFTP_H_

# include <unistd.h>
# include <netinet/in.h>

# define COMMAND_NUMBER		14

typedef enum
  {
    Unknown,
    LoginWithoutPass,
    Login,
    Logout,
  }		t_mode;

typedef enum
  {
    UNKNOWN,
    PASV,
    PORT
  }		t_type_server;

typedef struct			s_client
{
  int				fd;
  char				*ip;
  char				*pasvIp;
  struct sockaddr_in		s_in_client;
}				t_client;

typedef struct			s_command
{
  char				*path;
  char				*home_path;
  t_mode			mode;
  t_type_server			server_type;
  int				pasv_server_fd;
  char				*ip_active;
  int				port_active;
  char				*login;
}				t_command;

typedef struct			s_elem
{
  struct s_elem			*next;
  t_client			*client;
  pid_t				pid;
}				t_elem;

typedef struct			s_list
{
  t_elem			*begin;
  t_elem			*end;
}				t_list;

/*
**	get_client_mode.c
*/

void		client_ip_to_server(t_client *client);
t_client	*get_client_from_mode(t_command *command);

/*
**	passiv_exec.c
*/

int		passiv_list(t_client *client, char **tab,
			    t_command *command);
int		passiv_download(t_client *client, char **tab,
				t_command *command);
int		passiv_upload(t_client *client, char **tab,
			      t_command *command);

/*
**	exec_command.c
*/

int		send_command_to_client(char *command,
				       t_client *client);

/*
**	init_command.c
*/

void		init_string(char *command[COMMAND_NUMBER]);
void		init_fptr(int (*fptr[COMMAND_NUMBER])(t_client *,
						      char **,
						      t_command *));
void		init_command(t_command *command);

/*
**	command_mode.c
*/

int	on_pasv(t_client *client, char **tab, t_command *command);
int	on_port(t_client *client, char **tab, t_command *command);
int	on_help(t_client *client, char **tab, t_command *command);
int	on_noop(t_client *client, char **tab, t_command *command);

/*
**	command_actions.c
*/

int	on_stor(t_client *client, char **tab, t_command *command);
int	on_retr(t_client *client, char **tab, t_command *command);
int	on_list(t_client *client, char **tab, t_command *command);
int	on_dele(t_client *client, char **tab, t_command *command);
int	on_pwd(t_client *client, char **tab, t_command *command);

/*
**	command_login.c
*/

int	on_user(t_client *client, char **tab, t_command *command);
int	on_pass(t_client *client, char **tab, t_command *command);
int	on_cwd(t_client *client, char **tab, t_command *command);
int	on_cdup(t_client *client, char **tab, t_command *command);
int	on_quit(t_client *client, char **tab, t_command *command);

/*
**	get_data.c
*/

int		gestion_buffer(char *buffer, t_client *,
			       t_command *);
char		**split(char *str, char carac);

/*
**	server.c
*/

int		create_server(int const port);
int		run_server(int const server, char const *path);

/*
**	client_connection.c
*/

void			delete_client(t_client *client);
t_client		*get_client_from_server(int const fd_server);
int			send_msg_to_client(t_client const *client,
					   char const *msg);
char			*recv_msg_from_client(t_client const *client);
int			send_file_to_client(t_client const *client,
					    char const *file);

/*
**	server_connection.c
*/

int			get_fd_with_protocol_name(char const *protocole_name);
void			close_socket_fd(int const fd);
int		        bind_socketaddr(int const fd, int const port);
int			create_queue(int const fd, int const size);
t_client		*connect_to_socket(int const fd, char const *ip,
					   int const port);

#endif
