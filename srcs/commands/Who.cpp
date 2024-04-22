#include "Command.hpp"

Who::Who( Server *serv ): Command(serv) { }
Who::~Who( void ) { }

void    Who::execute( Client *sender, std::string args ) {
    (void)sender;
    /* si on envoie juste Who donner les infos sur TOUS les users */
    if (args.empty()) {
        std::cout << "WHO EVERYONE" << std::endl;
        return ;
    }
    
    /* si on envoie Who #... donner les infos sur TOUS les users du channel */
    if (args.at(0) == '#') {
        std::cout << "WHO CHAN " << args << std::endl;
        return ;
    }

    std::cout << "WHO MEC " << args << std::endl;
}