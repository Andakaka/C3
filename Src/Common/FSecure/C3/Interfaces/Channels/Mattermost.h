#pragma once
#include "Common/FSecure/Mattermost/MattermostApi.h"

namespace FSecure::C3::Interfaces::Channels
{
	///Implementation of the Mattermost Channel.
	struct Mattermost : public Channel<Mattermost>
	{
		/// Public constructor.
		/// @param arguments factory arguments.
		Mattermost(ByteView arguments);

		/// Destructor
		virtual ~Mattermost() = default;

		/// OnSend callback implementation.
		/// @param packet data to send to Channel.
		/// @returns size_t number of bytes successfully written.
		size_t OnSendToChannel(ByteView packet);

		/// Reads a single C3 packet from Channel.
		/// @return packet retrieved from Channel.
		std::vector<ByteVector> OnReceiveFromChannel();

		/// Get channel capability.
		/// @returns Channel capability in JSON format
		static const char* GetCapability();

		FSecure::ByteVector OnRunCommand(ByteView command) override;

		/// Values used as default for channel jitter. 30 ms if unset. Current jitter value can be changed at runtime.
		/// Set long delay otherwise Mattermost rate limit will heavily impact channel.
		constexpr static std::chrono::milliseconds s_MinUpdateDelay = 3500ms, s_MaxUpdateDelay = 6500ms;

	protected:
		/// The inbound direction name of data
		std::string m_inboundDirectionName;

		/// The outbound direction name, the opposite of m_inboundDirectionName
		std::string m_outboundDirectionName;

	private:
		/// An object encapsulating Mattermost's API, providing methods allowing the consumer to send and receive messages to Mattermost, among other things.
		FSecure::Mattermost m_MattermostObj;

		/// Delete all the replies to a message.
		/// @param repliesTs - an array of timestamps of messages to be deleted through DeleteMessage.
		void DeleteReplies(std::vector<std::string> const& postIDs);
	};
}
