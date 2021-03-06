/***************************************************************************
 *   Copyright (C) 2009 by                                                 *
 *   Joris Guisson <joris.guisson@gmail.com>                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
 ***************************************************************************/
#include "job.h"
#include "torrentcontrol.h"
#include <kio/jobuidelegate.h>
#include <kjobtrackerinterface.h>

namespace bt
{
	KJobTrackerInterface* Job::tracker = 0;
	
	Job::Job(bool stop_torrent, bt::TorrentControl* tc) : tc(tc),stop_torrent(stop_torrent)
	{
		setUiDelegate(new KIO::JobUiDelegate());
	}
	
	Job::~Job()
	{
	}

	void Job::start()
	{
	}
	
	void Job::kill(bool quietly)
	{
		if (!quietly)
		{
			setError(KIO::ERR_USER_CANCELED);
			emitResult();
		}
	}
	
	
	TorrentStatus Job::torrentStatus() const
	{
		return INVALID_STATUS;
	}
	
	void Job::setJobTracker(KJobTrackerInterface* trk)
	{
		tracker = trk;
	}
	
	void Job::registerWithTracker()
	{
		if (tracker)
			tracker->registerJob(this);
	}


}

