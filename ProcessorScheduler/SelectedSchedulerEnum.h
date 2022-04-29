#pragma once

/*! \brief Enum, containing all currently implemented schedulers.

	Note: SelectedScheduler::Unspecified defaults to one of the defined schedulers based on the implementation.
	In my implementation, it defaults to SelectedScheduler::Simple.
*/
enum class SelectedScheduler
{
	RoundRobin = 0,
	Simple = 1,
	Unspecified = 255
};