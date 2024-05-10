class GameManager:
    def __init__(self):
        self.teams = {}
        self.players = {}
        self.players_per_team = {}

    def launch_command(self, command, mode):
        if command == "Total goals for":
            return self.get_total_goals_for(mode)
        elif command == "Total goals by":
            return self.get_total_goals_by(mode)
        elif command == "Mean goals per game for":
            return self.get_mean_goals_per_game_for(mode)
        elif command == "Mean goals per game by":
            return self.get_mean_goals_per_game_by(mode)
        else:
            return self.get_score_opens(mode)

    def get_total_goals_for(self, mode):
        if mode in self.teams.keys():
            return self.teams[mode][0]
        else:
            return 0

    def get_total_goals_by(self, mode):
        if mode in self.players.keys():
            return self.players[mode][0]
        else:
            return 0

    def get_mean_goals_per_game_for(self, mode):
        if mode in self.teams.keys() and self.teams[mode][1] != 0:
            return self.teams[mode][0] / self.teams[mode][1]
        else:
            return 0

    def get_mean_goals_per_game_by(self, mode):
        if mode in self.players.keys() and self.players[mode][1] != 0:
            return self.players[mode][0] / self.players[mode][1]
        else:
            return 0

    def get_score_opens(self, mode):
        if '\"' in mode:
            if mode in self.teams.keys():
                return self.teams[mode][2]
            else:
                return 0
        else:
            if mode in self.players.keys():
                return self.players[mode][2]
            else:
                return 0

    """
        def get_goals_on_minute(self, mode):
            pass

        def get_goals_on_first(self, mode):
            pass

        def get_goals_on_last(self, mode):
            pass
    """


flag = False
neo_player = ""
neo_team = ""
mi = pow(10, 10)
unique_players_per_game_first_club = set()
unique_players_per_game_second_club = set()
goals_by_minute_current_match = {}
first_team_scored = 0
second_team_scored = 0

gm = GameManager()
f = open("input.txt", 'r')
out = open("output.txt", 'w')

for i in f.readlines():
    if ':' in i:
        if flag:
            if items[0] not in gm.players_per_team.keys():
                gm.players_per_team[items[0]] = unique_players_per_game_first_club
            else:
                for player in unique_players_per_game_first_club:
                    gm.players_per_team[items[0]].add(player)
            if items[1] not in gm.players_per_team.keys():
                gm.players_per_team[items[1]] = unique_players_per_game_second_club
            else:
                for player in unique_players_per_game_second_club:
                    gm.players_per_team[items[1]].add(player)
            for player in gm.players_per_team[items[0]]:
                gm.players[player][1] = gm.teams[items[0]][1]
            for player in gm.players_per_team[items[1]]:
                gm.players[player][1] = gm.teams[items[1]][1]
            if neo_player and neo_team:
                gm.players[neo_player][2] += 1
                gm.teams[neo_team][2] += 1
            flag = False

        flag = True
        neo_player = ""
        neo_team = ""
        mi = pow(10, 10)
        unique_players_per_game_first_club = set()
        unique_players_per_game_second_club = set()

        delimiters = ['-', ':']

        ind1 = i.index('-')
        ind2 = i.index(':')
        ind3 = ind2 - 1

        while i[ind3] != ' ':
            ind3 -= 1

        items = [i[:ind1 - 1], i[ind1 + 2:ind3], i[ind3 + 1:ind2], i[ind2 + 1:-1]]

        first_team_scored = int(items[2])
        second_team_scored = int(items[3])

        first_team_scores_first = True if int(items[2]) > 0 else False
        second_team_scores_first = True if int(items[2]) == 0 and int(items[3]) > 0 else False

        if items[0] not in gm.teams.keys():
            gm.teams[items[0]] = [int(items[2]), 1, 0]  # total goals, total games, total score opens
        else:
            gm.teams[items[0]][1] += 1
            gm.teams[items[0]][0] += int(items[2])

        if items[1] not in gm.teams.keys():
            gm.teams[items[1]] = [int(items[3]), 1, 0]
        else:
            gm.teams[items[1]][1] += 1
            gm.teams[items[1]][0] += int(items[3])
    else:
        if first_team_scored or second_team_scored:
            player_and_minute = i.split()
            player = ' '.join(player_and_minute[:-1])
            minute = int(player_and_minute[-1][:-1])

            if first_team_scored:
                first_team_scored -= 1
                unique_players_per_game_first_club.add(player)
                if minute < mi:
                    mi = minute
                    neo_player = player
                    neo_team = items[0]
            elif second_team_scored:
                second_team_scored -= 1
                unique_players_per_game_second_club.add(player)
                if minute < mi:
                    mi = minute
                    neo_player = player
                    neo_team = items[1]

            if player not in gm.players.keys():
                gm.players[player] = [1, 0, 0]  # total goals, total games, total score opens
            else:
                gm.players[player][0] += 1

            if player not in goals_by_minute_current_match.keys():
                goals_by_minute_current_match[player] = [minute]
            else:
                goals_by_minute_current_match[player].append(minute)
        else:
            if flag:
                if items[0] not in gm.players_per_team.keys():
                    gm.players_per_team[items[0]] = unique_players_per_game_first_club
                else:
                    for player in unique_players_per_game_first_club:
                        gm.players_per_team[items[0]].add(player)
                if items[1] not in gm.players_per_team.keys():
                    gm.players_per_team[items[1]] = unique_players_per_game_second_club
                else:
                    for player in unique_players_per_game_second_club:
                        gm.players_per_team[items[1]].add(player)
                for player in gm.players_per_team[items[0]]:
                    gm.players[player][1] = gm.teams[items[0]][1]
                for player in gm.players_per_team[items[1]]:
                    gm.players[player][1] = gm.teams[items[1]][1]
                if neo_player and neo_team:
                    gm.players[neo_player][2] += 1
                    gm.teams[neo_team][2] += 1
                flag = False

            command_and_mode = i.split()

            if command_and_mode[2] == "minute":
                player = ' '.join(command_and_mode[command_and_mode.index("by") + 1:])
                value = int(command_and_mode[3])
                if player in goals_by_minute_current_match.keys():
                    minutes = goals_by_minute_current_match[player]
                    k = 0
                    for minute in minutes:
                        if minute == value:
                            k += 1
                    out.write(str(k) + '\n')
                else:
                    out.write(str(0) + '\n')
            elif command_and_mode[2] == "first":
                player = ' '.join(command_and_mode[command_and_mode.index("by") + 1:])
                value = int(command_and_mode[3])
                if player in goals_by_minute_current_match.keys():
                    minutes = goals_by_minute_current_match[player]
                    k = 0
                    for minute in minutes:
                        if minute <= value:
                            k += 1
                    out.write(str(k) + '\n')
                else:
                    out.write(str(0) + '\n')
            elif command_and_mode[2] == "last":
                player = ' '.join(command_and_mode[command_and_mode.index("by") + 1:])
                value = int(command_and_mode[3])
                if player in goals_by_minute_current_match.keys():
                    minutes = goals_by_minute_current_match[player]
                    k = 0
                    for minute in minutes:
                        if minute >= 91 - value:
                            k += 1
                    out.write(str(k) + '\n')
                else:
                    out.write(str(0) + '\n')
            else:
                ind = 0
                if "for" in command_and_mode:
                    ind = command_and_mode.index("for")
                elif "by" in command_and_mode:
                    ind = command_and_mode.index("by")
                command = ' '.join(command_and_mode[:ind + 1])
                mode = ' '.join(command_and_mode[ind + 1:])
                s = str(gm.launch_command(command, mode)) + '\n'
                out.write(str(gm.launch_command(command, mode)) + '\n')