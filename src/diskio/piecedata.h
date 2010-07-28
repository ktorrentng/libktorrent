/***************************************************************************
 *   Copyright (C) 2008 by Joris Guisson and Ivan Vasic                    *
 *   joris.guisson@gmail.com                                               *
 *   ivasic@gmail.com                                                      *
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
#ifndef BTPIECEDATA_H
#define BTPIECEDATA_H

#include <ktorrent_export.h>
#include <util/constants.h>
#ifndef Q_CC_MSVC
#include <util/signalcatcher.h>
#endif
#include <diskio/cachefile.h>


namespace bt
{
	class Chunk;

	/**
		Class which holds the data of a piece of a chunk.
		It has a reference counter.
	*/
	class KTORRENT_EXPORT PieceData : public MMappeable
	{
	public:
		PieceData(Chunk* chunk,Uint32 off,Uint32 len,Uint8* ptr,CacheFile* file);
		virtual ~PieceData();
		
		/// Is this in use (i.e. can we unload it
		bool inUse() const {return ref_count > 0;}
		
		/// Is it a mapped into memory
		bool mapped() const {return file != 0;}
		
		/// Get the offset of the piece in the chunk
		Uint32 offset() const {return off;}
		
		/// Get the length of the piece
		Uint32 length() const {return len;}
		
		/// Get a pointer to the data
		Uint8* data() {return ptr;}
		
		/// Set the data pointer
		void setData(Uint8* p) {ptr = p;}

		/// Unload the data (in mapped mode, this means save to disk)
		void unload();

		/// Get the parent chunk of the piece
		Chunk* parentChunk() {return chunk;}
		
		/**
			Write data into the PieceData. This function should always be used 
			for writing into a PieceData object, as it protects against bus errors.
			@param buf The buffer to write
			@param size Size of the buffer
			@param off Offset to write
			@return The number of bytes written
			@throw BusError When writing results in a SIGBUS
		*/
#ifndef Q_CC_MSVC
		Uint32 write(const Uint8* buf,Uint32 buf_size,Uint32 off = 0) throw (BusError);
#else
		Uint32 write(const Uint8* buf,Uint32 buf_size,Uint32 off = 0);
#endif

	private:
		virtual void unmapped();
		
		/// Increase the reference counter
		void ref() {ref_count++;}
		
		/// Decrease the reference counter
		void unref() {ref_count--;}

	private:
		Chunk* chunk;
		Uint32 off;
		Uint32 len;
		Uint8* ptr;
		CacheFile* file;
		int ref_count;
		
		friend class PieceDataPtr;
	};
	
	/**
		Smart pointer class for PieceData
	*/
	class KTORRENT_EXPORT PieceDataPtr
	{
	public:
		PieceDataPtr(PieceData* pdata = 0);
		PieceDataPtr(const PieceDataPtr & pdata);
		~PieceDataPtr();
		
		PieceData & operator * () const {return *pdata;}
		PieceData* operator -> () const {return pdata;}
		PieceDataPtr & operator = (const PieceDataPtr & pdata);
		operator bool () const {return pdata != 0;}
		void reset();
		
	private:
		PieceData* pdata;
	};

}

#endif
