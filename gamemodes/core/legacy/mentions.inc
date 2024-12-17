// built-in include guard removal
// just in case the user has a local dependency with the same file name
#if defined _inc_mentions
    #undef _inc_mentions
#endif
// custom include-guard to ensure we don't duplicate
#if defined _mentions_included
	#endinput
#endif
#define _mentions_included

#include <a_samp>
#include <YSI_Server\y_colours>


enum E_COLOUR_EMBED_DATA {
	ce_char,
	ce_colour[9]
}

static embedColours[8][E_COLOUR_EMBED_DATA] = {
	{'r', RED},
	{'g', GREEN},
	{'b', BLUE},
	{'y', YELLOW},
	{'p', PINK},
	{'w', WHITE},
	{'o', ORANGE},
	{'n', NAVY}
};

stock FindMention(const input[], begin) {
	new size = strlen(input), id[24];

	for(new i = begin+1; i < size; i++) {
		if(_mentions_isNumeric(input[i])) {
			strcat(id, input[i]);
		}
	}

	if(strlen(id) == 0)
		return INVALID_PLAYER_ID;

	new numberid = strval(id);
	if(!Player_Logado(numberid))
		return INVALID_PLAYER_ID;

	return numberid;
}

stock ExpandMentions(const input[], output[], outCap, colour) {
	new
		inLen = strlen(input),
		outLen = 0,
		index,
		numTags,
		mentionID,
		mentionName[MAX_PLAYER_NAME+17],
		mentionColour[9],
		endColour[9],
		colourEmbed,
		bool:skip;

	format(endColour, sizeof(endColour), "{%06x}", colour >>> 8);

	for( ; index < inLen && outLen < outCap; ++index) {
		if(input[index] == '@' && numTags < 3) {
			mentionID = FindMention(input, index);
			if(mentionID != INVALID_PLAYER_ID) {
				GetPlayerName(mentionID, mentionName, MAX_PLAYER_NAME);
				format(mentionColour, sizeof(mentionColour), "{%06x}", GetPlayerColor(mentionID) >>> 8);

				// concatenate the player's colour code, their name and then reset the colour
				strcat(output, mentionColour, outCap);
				strcat(output, mentionName, outCap);
				strcat(output, endColour, outCap);

				// update the output string length
				outLen += 8 + strlen(mentionName) + 8;

				new strMentionID[5];
				valstr(strMentionID, mentionID);
				index += (strlen(strMentionID) - 1);

				numTags++;
				skip = true;
			}
		} else if(input[index] == '&' && numTags < 3) {
			if(_mentions_isAlphabetic(input[index + 1])) {
				colourEmbed = _mentions_getEmbedColourIdx(input[index + 1]);
				if(colourEmbed != -1) {
					strcat(output, embedColours[colourEmbed][ce_colour], outCap);

					// update the output string length
					outLen += 8;

					numTags++;
					skip = true;
				}
			}
		} else {
			if(skip) {
				skip = false;
				continue;
			}

			output[outLen++] = input[index];
		}
	}

	return numTags;
}

stock _mentions_getEmbedColourIdx(ch) {
	for(new i; i < sizeof(embedColours); i++) {
		if(ch == embedColours[i][ce_char]) {
			return i;
		}
	}
	return -1;
}

stock _mentions_isNumeric(ch) {
	if(ch >= '0' && ch <= '9') {
		return true;
	}
	return false;
}

stock _mentions_isAlphabetic(ch) {
	if( (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
		return true;
	}
	return false;
}