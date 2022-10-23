#include "Sanity.h"
#include "cfg.h"
#include <dpp/dpp.h>
#include <iostream>
#include <string>

std::string botname;
int main() {
	std::cout << "[+]Bot Starting\n";
	dpp::cluster bot(bot_token, dpp::i_default_intents);
	bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
		dpp::command_interaction cmdd = event.command.get_command_interaction();
		if (event.command.get_command_name() == "moyai") {
			event.reply("Histic isn fag!");
		}
		if (event.command.get_command_name() == "help") {
			dpp::embed embed = dpp::embed().
				set_title("help").
				add_field(
					"help",
					"keine ahnung",
					true
				).
				set_url("https://xyzz1887.xyz").
				set_timestamp(time(0));
			dpp::message repl(event.command.channel_id, embed);
			event.reply(repl);
		}
		if (event.command.get_command_name() == "ban") {
			if (cmdd.options.size() > 0) {
				
				dpp::snowflake usr = std::get<dpp::snowflake>(cmdd.options[0].value);
				dpp::embed embed = dpp::embed().
					set_title("Banned").
					set_description("Banned: <@" + std::to_string(usr) + ">").
					set_footer(dpp::embed_footer().set_text("Sukuna")).
					set_timestamp(time(0));
					
					

				bot.guild_ban_add(event.command.guild_id, usr);
				dpp::message repl(event.command.channel_id, embed);
				event.reply(repl);
				}
			
			}
		});
	
	bot.on_ready([&bot](const dpp::ready_t& event) {
		if(dpp::run_once <struct initalize>()) {
			std::cout << "[+]Started\n";
			botname = bot.me.username;
		}
		if (dpp::run_once<struct register_bot_commands>()) {
			auto mute_permission = dpp::command_permission();
			
			dpp::slashcommand ban("ban", "bans a player", bot.me.id);
			ban.add_option(dpp::command_option(dpp::co_user, "user", "User to ban.", true));
			ban.set_default_permissions(dpp::p_ban_members);
			bot.global_command_create(dpp::slashcommand("help", "shows list of commands", bot.me.id)),
			bot.global_command_create(ban);
			
			
		}
		});

	bot.start(dpp::st_wait);
}