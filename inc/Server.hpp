//
// Created by rdas-nev on 4/19/23.
//

#ifndef INC_42_FT_IRC_SERVER_H
#define INC_42_FT_IRC_SERVER_H

#include "ft_irc.hpp"

class User;
class Channel;

class Server
{
		const std::string 		password;
        const std::string   	oper_auth; // pass for op is: operador
		int 					socket_fd;
		struct sockaddr_in		server_addr;
		int						epoll_fd;
        struct epoll_event 		event;
        std::vector<Channel>	channels;
        std::map<int, User>		users;
        std::vector<int>		server_ops;
public:
	// Constructor
		Server(int prt, char *pd);
	// Getters
		const std::string	&getPassword() const { return password;}
		const int 			&getSocketFd() const {return socket_fd;}
		const int 			&getEpollFd() const {return epoll_fd;}
		struct epoll_event	&getEvent() {return event;}
		std::vector<Channel> &getChannels() {return channels;}
		std::map<int, User> &getUsers() {return users;}
	// Managing new and existing clients
		void processClient(int client_fd, const std::string& password);
		void setNICK(int fd);
        void setUSER(int fd);
		void newClient();
		void existingClient(int fd);
		int clientFd(std::string &nick);
		bool validateNickUser(std::string &name, int client_fd, int flag);
	// Commands
		void commandmaster(std::string buf, int fd);
		void commands(std::string buf, int fd);
		int pass(std::vector<std::string> blocks, int fd);
		int nick(std::vector<std::string> blocks, int fd);
		int user(std::vector<std::string> blocks, int fd);
		int join(std::vector<std::string> blocks, int fd);
		int msg(std::vector<std::string> blocks, int fd);
		int notice(std::vector<std::string> blocks, int fd);
		int part(std::vector<std::string> blocks, int fd);
        int oper(std::vector<std::string> blocks, int fd);
        int kick(std::vector<std::string> blocks, int fd);
        int invite(std::vector<std::string> blocks, int fd);
        int topic(std::vector<std::string> blocks, int fd);
		int mode(std::vector<std::string> blocks, int fd);
	// Signals
		static void ctrlc(int sig);
	// Run server
		void run();
	// Destructor
		~Server();
};

#endif //INC_42_FT_IRC_SERVER_H
