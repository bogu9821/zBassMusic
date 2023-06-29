#include "Union.h"
#include <ZenGin/zGothicAPI.h>
#include <NH/BassOptions.h>

namespace NH
{
	namespace Log
	{
		inline bool ShouldLog(Level level, Union::StringUTF8 config)
		{
			if (level == Level::DEBUG) return config == "DEBUG";
			if (level == Level::INFO) return config == "DEBUG" || config == "INFO";
			if (level == Level::WARN) return config == "DEBUG" || config == "INFO" || config == "WARN";
			if (level == Level::ERROR) return config == "DEBUG" || config == "INFO" || config == "WARN" || config == "ERROR";
			return false;
		}

		void Message(Level level, Union::StringUTF8 channel, Union::StringUTF8 message)
		{
			if (ShouldLog(level, NH::Bass::Options.LoggerLevelUnion)) {
				Union::StringUTF8 output = "";
				switch (level)
				{
				case Level::DEBUG:
					output = Union::StringUTF8::Format("\x1B[1;97;45mzBassMusic DEBUG \x1B[0m\x1B[95m %s: %s", channel, message);
					break;
				case Level::INFO:
					output = Union::StringUTF8::Format("\x1B[1m\x1B[37m\x1B[44mzBassMusic  INFO \x1B[0m\x1B[94m %s: %s", channel, message);
					break;
				case Level::WARN:
					output = Union::StringUTF8::Format("\x1B[1m\x1B[37m\x1B[43mzBassMusic  WARN \x1B[0m\x1B[93m %s: %s", channel, message);
					break;
				case Level::ERROR:
					output = Union::StringUTF8::Format("\x1B[1m\x1B[97m\x1B[41mzBassMusic ERROR \x1B[0m\x1B[91m %s: %s", channel, message);
					break;
				}
				output.StdPrintLine();
			}

			if (ShouldLog(level, NH::Bass::Options.LoggerLevelZSpy)) {
				if (GetGameVersion() == Engine_G1)
				{
					auto msg = Gothic_I_Classic::zSTRING("B:\tBASSMUSIC: ") + Gothic_I_Classic::zSTRING(channel.ToChar()) + Gothic_I_Classic::zSTRING(": ") + Gothic_I_Classic::zSTRING(message.ToChar());
					Gothic_I_Classic::zerr->Message(msg);
				}

				if (GetGameVersion() == Engine_G2A)
				{
					auto msg = Gothic_II_Addon::zSTRING("B:\tBASSMUSIC: ") + Gothic_II_Addon::zSTRING(channel.ToChar()) + Gothic_II_Addon::zSTRING(": ") + Gothic_II_Addon::zSTRING(message.ToChar());
					Gothic_II_Addon::zerr->Message(msg);
				}
			}
		}
	}
}