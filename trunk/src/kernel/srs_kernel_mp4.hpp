/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2013-2017 OSSRS(winlin)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef SRS_KERNEL_MP4_HPP
#define SRS_KERNEL_MP4_HPP

#include <srs_core.hpp>

#include <srs_kernel_buffer.hpp>
#include <srs_kernel_codec.hpp>

#include <string>
#include <vector>
#include <map>

class ISrsWriteSeeker;
class ISrsReadSeeker;
class SrsMp4TrackBox;
class SrsMp4MediaBox;
class SrsSimpleStream;
class SrsMp4MovieHeaderBox;
class SrsMp4TrackHeaderBox;
class SrsMp4SampleTableBox;
class SrsMp4MediaInformationBox;
class SrsMp4SampleDescriptionBox;
class SrsMp4AvccBox;
class SrsMp4DecoderSpecificInfo;
class SrsMp4VisualSampleEntry;
class SrsMp4AvccBox;
class SrsMp4AudioSampleEntry;
class SrsMp4EsdsBox;
class SrsMp4ChunkOffsetBox;
class SrsMp4SampleSizeBox;
class SrsMp4Sample2ChunkBox;
class SrsMp4DecodingTime2SampleBox;
class SrsMp4CompositionTime2SampleBox;
class SrsMp4SyncSampleBox;
class SrsMp4MediaHeaderBox;
class SrsMp4HandlerReferenceBox;
class SrsMp4VideoMeidaHeaderBox;
class SrsMp4DataInformationBox;
class SrsMp4DataReferenceBox;
class SrsMp4SoundMeidaHeaderBox;
class SrsMp4MovieExtendsBox;
class SrsMp4TrackExtendsBox;

/**
 * 4.2 Object Structure
 * ISO_IEC_14496-12-base-format-2012.pdf, page 16
 */
enum SrsMp4BoxType
{
    SrsMp4BoxTypeForbidden = 0x00,
    
    SrsMp4BoxTypeUUID = 0x75756964, // 'uuid'
    SrsMp4BoxTypeFTYP = 0x66747970, // 'ftyp'
    SrsMp4BoxTypeMDAT = 0x6d646174, // 'mdat'
    SrsMp4BoxTypeFREE = 0x66726565, // 'free'
    SrsMp4BoxTypeSKIP = 0x736b6970, // 'skip'
    SrsMp4BoxTypeMOOV = 0x6d6f6f76, // 'moov'
    SrsMp4BoxTypeMVHD = 0x6d766864, // 'mvhd'
    SrsMp4BoxTypeTRAK = 0x7472616b, // 'trak'
    SrsMp4BoxTypeTKHD = 0x746b6864, // 'tkhd'
    SrsMp4BoxTypeEDTS = 0x65647473, // 'edts'
    SrsMp4BoxTypeELST = 0x656c7374, // 'elst'
    SrsMp4BoxTypeMDIA = 0x6d646961, // 'mdia'
    SrsMp4BoxTypeMDHD = 0x6d646864, // 'mdhd'
    SrsMp4BoxTypeHDLR = 0x68646c72, // 'hdlr'
    SrsMp4BoxTypeMINF = 0x6d696e66, // 'minf'
    SrsMp4BoxTypeVMHD = 0x766d6864, // 'vmhd'
    SrsMp4BoxTypeSMHD = 0x736d6864, // 'smhd'
    SrsMp4BoxTypeDINF = 0x64696e66, // 'dinf'
    SrsMp4BoxTypeURL  = 0x75726c20, // 'url '
    SrsMp4BoxTypeURN  = 0x75726e20, // 'urn '
    SrsMp4BoxTypeDREF = 0x64726566, // 'dref'
    SrsMp4BoxTypeSTBL = 0x7374626c, // 'stbl'
    SrsMp4BoxTypeSTSD = 0x73747364, // 'stsd'
    SrsMp4BoxTypeSTTS = 0x73747473, // 'stts'
    SrsMp4BoxTypeCTTS = 0x63747473, // 'ctts'
    SrsMp4BoxTypeSTSS = 0x73747373, // 'stss'
    SrsMp4BoxTypeSTSC = 0x73747363, // 'stsc'
    SrsMp4BoxTypeSTCO = 0x7374636f, // 'stco'
    SrsMp4BoxTypeCO64 = 0x636f3634, // 'co64'
    SrsMp4BoxTypeSTSZ = 0x7374737a, // 'stsz'
    SrsMp4BoxTypeSTZ2 = 0x73747a32, // 'stz2'
    SrsMp4BoxTypeAVC1 = 0x61766331, // 'avc1'
    SrsMp4BoxTypeAVCC = 0x61766343, // 'avcC'
    SrsMp4BoxTypeMP4A = 0x6d703461, // 'mp4a'
    SrsMp4BoxTypeESDS = 0x65736473, // 'esds'
    SrsMp4BoxTypeUDTA = 0x75647461, // 'udta'
    SrsMp4BoxTypeMVEX = 0x6d766578, // 'mvex'
    SrsMp4BoxTypeTREX = 0x74726578, // 'trex'
    
    SrsMp4BoxTypePASP = 0x70617370, // 'pasp'
};

/**
 * 8.4.3.3 Semantics
 * ISO_IEC_14496-12-base-format-2012.pdf, page 37
 */
enum SrsMp4HandlerType
{
    SrsMp4HandlerTypeForbidden = 0x00,
    
    SrsMp4HandlerTypeVIDE = 0x76696465, // 'vide'
    SrsMp4HandlerTypeSOUN = 0x736f756e, // 'soun'
};

/**
 * File format brands
 * ISO_IEC_14496-12-base-format-2012.pdf, page 166
 */
enum SrsMp4BoxBrand
{
    SrsMp4BoxBrandForbidden = 0x00,
    SrsMp4BoxBrandISOM = 0x69736f6d, // 'isom'
    SrsMp4BoxBrandISO2 = 0x69736f32, // 'iso2'
    SrsMp4BoxBrandAVC1 = 0x61766331, // 'avc1'
    SrsMp4BoxBrandMP41 = 0x6d703431, // 'mp41'
    SrsMp4BoxBrandISO5 = 0x69736f35, // 'iso5'
    SrsMp4BoxBrandMP42 = 0x6d703432, // 'mp42'
    SrsMp4BoxBrandDASH = 0x64617368, // 'dash'
};

/**
 * 4.2 Object Structure
 * ISO_IEC_14496-12-base-format-2012.pdf, page 16
 */
class SrsMp4Box : public ISrsCodec
{
private:
    // The size is the entire size of the box, including the size and type header, fields,
    // and all contained boxes. This facilitates general parsing of the file.
    //
    // if size is 1 then the actual size is in the field largesize;
    // if size is 0, then this box is the last one in the file, and its contents
    // extend to the end of the file (normally only used for a Media Data Box)
    uint32_t smallsize;
    uint64_t largesize;
public:
    // identifies the box type; standard boxes use a compact type, which is normally four printable
    // characters, to permit ease of identification, and is shown so in the boxes below. User extensions use
    // an extended type; in this case, the type field is set to ‘uuid’.
    SrsMp4BoxType type;
    // For box 'uuid'.
    std::vector<char> usertype;
protected:
    std::vector<SrsMp4Box*> boxes;
private:
    // The position at buffer to start demux the box.
    int start_pos;
public:
    SrsMp4Box();
    virtual ~SrsMp4Box();
public:
    // Get the size of box, whatever small or large size.
    // @remark For general box(except mdat), we use this sz() to create the buffer to codec it.
    virtual uint64_t sz();
    // Get the size of header, without contained boxes.
    // @remark For mdat box, we must codec its header, use this instead of sz().
    virtual int sz_header();
    // Get the left space of box, for decoder.
    virtual int left_space(SrsBuffer* buf);
    // Box type helper.
    virtual bool is_ftyp();
    virtual bool is_moov();
    virtual bool is_mdat();
    // Get the contained box of specific type.
    // @return The first matched box.
    virtual SrsMp4Box* get(SrsMp4BoxType bt);
    // Remove the contained box of specified type.
    // @return The removed count.
    virtual int remove(SrsMp4BoxType bt);
    /**
     * Discovery the box from buffer.
     * @param ppbox Output the discoveried box, which user must free it.
     */
    static int discovery(SrsBuffer* buf, SrsMp4Box** ppbox);
// Interface ISrsCodec
public:
    virtual int nb_bytes();
    virtual int encode(SrsBuffer* buf);
    virtual int decode(SrsBuffer* buf);
protected:
    virtual int encode_boxes(SrsBuffer* buf);
    virtual int decode_boxes(SrsBuffer* buf);
// Sub classes can override these functions for special codec.
// @remark For mdat box, we use completely different codec.
protected:
    // The size of header, not including the contained boxes.
    virtual int nb_header();
    // It's not necessary to check the buffer, because we already know the size in parent function,
    // so we have checked the buffer is ok to write.
    virtual int encode_header(SrsBuffer* buf);
    // It's not necessary to check the buffer, unless the box is not only determined by the verson.
    // Generally, it's not necessary, that is, all boxes is determinated by version.
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 4.2 Object Structure
 * ISO_IEC_14496-12-base-format-2012.pdf, page 17
 */
class SrsMp4FullBox : public SrsMp4Box
{
public:
    // an integer that specifies the version of this format of the box.
    uint8_t version;
    // a map of flags
    uint32_t flags;
public:
    SrsMp4FullBox();
    virtual ~SrsMp4FullBox();
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 4.3 File Type Box (ftyp)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 17
 * Files written to this version of this specification must contain a file-type box. For compatibility with an earlier
 * version of this specification, files may be conformant to this specification and not contain a file-type box. Files
 * with no file-type box should be read as if they contained an FTYP box with Major_brand='mp41', minor_version=0, and
 * the single compatible brand 'mp41'.
 */
class SrsMp4FileTypeBox : public SrsMp4Box
{
public:
    // a brand identifier
    SrsMp4BoxBrand major_brand;
    // an informative integer for the minor version of the major brand
    uint32_t minor_version;
private:
    // a list, to the end of the box, of brands
    std::vector<SrsMp4BoxBrand> compatible_brands;
public:
    SrsMp4FileTypeBox();
    virtual ~SrsMp4FileTypeBox();
public:
    virtual void set_compatible_brands(SrsMp4BoxBrand b0, SrsMp4BoxBrand b1, SrsMp4BoxBrand b2, SrsMp4BoxBrand b3);
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.1.1 Media Data Box (mdat)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 29
 * This box contains the media data. In video tracks, this box would contain video frames.
 * A presentation may contain zero or more Media Data Boxes. The actual media data follows the type field;
 * its structure is described by the metadata (see particularly the sample table, subclause 8.5, and the
 * item location box, subclause 8.11.3).
 * 
 * @remark The mdat box only decode and encode the header,
 *      so user must read and write the data by yourself.
 * To encode mdat:
 *      SrsMp4MediaDataBox* mdat = new SrsMp4MediaDataBox();
 *      mdat->nb_data = 1024000;
 *
 *      char* buffer = new char[mdat->sz_header()];
 *      SrsBuffer* buf = new SrsBuffer(buffer);
 *      mdat->encode(buf);
 *      
 *      file->write(buffer, mdat->sz_header()); // Write the mdat box header.
 *      file->write(data, size); // Write the mdat box data.
 * 
 * To decode mdat:
 *      SrsMp4MediaDataBox* mdat = new SrsMp4MediaDataBox();
 *      char* buffer = new char[mdat->sz_header()];
 *      SrsBuffer* buf = ...; // Read mdat->sz_header() data from io.
 * 
 *      mdat->decode(buf); // The buf should be empty now.
 *      file->lseek(mdat->nb_data, SEEK_CUR); // Skip the mdat data in file.
 * 
 * To discovery any box from file:
 *      SrsSimpleStream* stream = new SrsSimpleStream();
 *      SrsBuffer* buf = new SrsBuffer(stream...); // Create read buffer from stream.
 *      
 *      // We don't know what's the next box, so try to read 4bytes and discovery it.
 *      append(file, stream, 4); // Append 4bytes from file to stream.
 *
 *      SrsMp4Box* box = NULL;
 *      SrsMp4Box::discovery(buf, &box);
 *
 *      required = (box->is_mdat()? box->sz_header():box->sz()); // Now we know how many bytes we needed.
 *      append(file, stream, required);
 *      box->decode(buf);
 *
 *      if (box->is_mdat()) {
 *          file->lseek(mdat->nb_data, SEEK_CUR); // Skip the mdat data in file.
 *      }
 */
class SrsMp4MediaDataBox : public SrsMp4Box
{
public:
    // The contained media data, which we never directly read/write it.
    // TODO: FIXME: Support 64bits size.
    int nb_data;
public:
    SrsMp4MediaDataBox();
    virtual ~SrsMp4MediaDataBox();
// Interface ISrsCodec
public:
    // The total size of bytes, including the sz_header() and nb_data,
    // which used to write the smallsize or largesize of mp4.
    virtual int nb_bytes();
    // To encode the mdat box, the buf should only contains the sz_header(),
    // because the mdata only encode the header.
    virtual int encode(SrsBuffer* buf);
    // To decode the mdat box, the buf should only contains the sz_header(),
    // because the mdat only decode the header.
    virtual int decode(SrsBuffer* buf);
protected:
    virtual int encode_boxes(SrsBuffer* buf);
    virtual int decode_boxes(SrsBuffer* buf);
};

/**
 * 8.1.2 Free Space Box (free or skip)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 29
 */
class SrsMp4FreeSpaceBox : public SrsMp4Box
{
private:
    std::vector<char> data;
public:
    SrsMp4FreeSpaceBox();
    virtual ~SrsMp4FreeSpaceBox();
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.2.1 Movie Box (moov)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 30
 * The metadata for a presentation is stored in the single Movie Box which occurs at the top-level of a file.
 * Normally this box is close to the beginning or end of the file, though this is not required.
 */
class SrsMp4MovieBox : public SrsMp4Box
{
public:
    SrsMp4MovieBox();
    virtual ~SrsMp4MovieBox();
public:
    // Get the header of moov.
    virtual SrsMp4MovieHeaderBox* mvhd();
    virtual void set_mvhd(SrsMp4MovieHeaderBox* v);
    // Get the movie extends header.
    virtual SrsMp4MovieExtendsBox* mvex();
    virtual void set_mvex(SrsMp4MovieExtendsBox* v);
    // Get the first video track.
    virtual SrsMp4TrackBox* video();
    // Get the first audio track.
    virtual SrsMp4TrackBox* audio();
    // Add a new track.
    virtual void add_trak(SrsMp4TrackBox* v);
    // Get the number of video tracks.
    virtual int nb_vide_tracks();
    // Get the number of audio tracks.
    virtual int nb_soun_tracks();
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.2.2 Movie Header Box (mvhd)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 31
 */
class SrsMp4MovieHeaderBox : public SrsMp4FullBox
{
public:
    // an integer that declares the creation time of the presentation (in seconds since
    // midnight, Jan. 1, 1904, in UTC time)
    uint64_t creation_time;
    // an integer that declares the most recent time the presentation was modified (in
    // seconds since midnight, Jan. 1, 1904, in UTC time)
    uint64_t modification_time;
public:
    // an integer that specifies the time-scale for the entire presentation; this is the number of
    // time units that pass in one second. For example, a time coordinate system that measures time in
    // sixtieths of a second has a time scale of 60.
    uint32_t timescale;
    // an integer that declares length of the presentation (in the indicated timescale). This property
    // is derived from the presentation’s tracks: the value of this field corresponds to the duration of the
    // longest track in the presentation. If the duration cannot be determined then duration is set to all 1s.
    uint64_t duration_in_tbn;
public:
    // a fixed point 16.16 number that indicates the preferred rate to play the presentation; 1.0
    // (0x00010000) is normal forward playback
    uint32_t rate;
    // a fixed point 8.8 number that indicates the preferred playback volume. 1.0 (0x0100) is full volume.
    uint16_t volume;
    uint16_t reserved0;
    uint64_t reserved1;
    // a transformation matrix for the video; (u,v,w) are restricted here to (0,0,1), hex values (0,0,0x40000000).
    int32_t matrix[9];
    uint32_t pre_defined[6];
    // a non-zero integer that indicates a value to use for the track ID of the next track to be
    // added to this presentation. Zero is not a valid track ID value. The value of next_track_ID shall be
    // larger than the largest track-ID in use. If this value is equal to all 1s (32-bit maxint), and a new media
    // track is to be added, then a search must be made in the file for an unused track identifier.
    uint32_t next_track_ID;
public:
    SrsMp4MovieHeaderBox();
    virtual ~SrsMp4MovieHeaderBox();
public:
    // Get the duration in ms.
    virtual uint64_t duration();
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

// The type of track, maybe combine of types.
enum SrsMp4TrackType
{
    SrsMp4TrackTypeForbidden = 0x00,
    SrsMp4TrackTypeAudio = 0x01,
    SrsMp4TrackTypeVideo = 0x02,
};

/**
 * 8.8.1 Movie Extends Box (mvex)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 64
 * This box warns readers that there might be Movie Fragment Boxes in this file. To know of all samples in the
 * tracks, these Movie Fragment Boxes must be found and scanned in order, and their information logically
 * added to that found in the Movie Box.
 */
class SrsMp4MovieExtendsBox : public SrsMp4Box
{
public:
    SrsMp4MovieExtendsBox();
    virtual ~SrsMp4MovieExtendsBox();
public:
    // Get the track extends box.
    virtual SrsMp4TrackExtendsBox* trex();
    virtual void set_trex(SrsMp4TrackExtendsBox* v);
};

/**
 * 8.8.3 Track Extends Box(trex)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 65
 */
class SrsMp4TrackExtendsBox : public SrsMp4FullBox
{
public:
    // identifies the track; this shall be the track ID of a track in the Movie Box
    uint32_t track_ID;
    // these fields set up defaults used in the track fragments.
    uint32_t default_sample_description_index;
    uint32_t default_sample_duration;
    uint32_t default_sample_size;
    uint32_t default_sample_flags;
public:
    SrsMp4TrackExtendsBox();
    virtual ~SrsMp4TrackExtendsBox();
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.3.1 Track Box (trak)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 32
 * This is a container box for a single track of a presentation. A presentation consists of one or more tracks.
 * Each track is independent of the other tracks in the presentation and carries its own temporal and spatial
 * information. Each track will contain its associated Media Box.
 */
class SrsMp4TrackBox : public SrsMp4Box
{
public:
    SrsMp4TrackBox();
    virtual ~SrsMp4TrackBox();
public:
    // Get the type of track, maybe combine of track type,
    // for example, it maybe Audio|Video when contains both.
    // Generally, only single type, no combination.
    virtual SrsMp4TrackType track_type();
    // Get the track header box.
    virtual SrsMp4TrackHeaderBox* tkhd();
    virtual void set_tkhd(SrsMp4TrackHeaderBox* v);
public:
    // Get the chunk offset box.
    virtual SrsMp4ChunkOffsetBox* stco();
    // Get the sample size box.
    virtual SrsMp4SampleSizeBox* stsz();
    // Get the sample to chunk box.
    virtual SrsMp4Sample2ChunkBox* stsc();
    // Get the dts box.
    virtual SrsMp4DecodingTime2SampleBox* stts();
    // Get the cts/pts box.
    virtual SrsMp4CompositionTime2SampleBox* ctts();
    // Get the sync dts box.
    virtual SrsMp4SyncSampleBox* stss();
    // Get the media header box.
    virtual SrsMp4MediaHeaderBox* mdhd();
public:
    // For vide track, get the video codec.
    virtual SrsVideoCodecId vide_codec();
    // For soun track, get the audio codec.
    virtual SrsAudioCodecId soun_codec();
    // For H.264/AVC codec, get the sps/pps.
    virtual SrsMp4AvccBox* avcc();
    // For AAC codec, get the asc.
    virtual SrsMp4DecoderSpecificInfo* asc();
public:
    // Get the media box.
    virtual SrsMp4MediaBox* mdia();
    virtual void set_mdia(SrsMp4MediaBox* v);
    // Get the media info box.
    virtual SrsMp4MediaInformationBox* minf();
    // Get the sample table box.
    virtual SrsMp4SampleTableBox* stbl();
    // Get the sample description box
    virtual SrsMp4SampleDescriptionBox* stsd();
public:
    // For H.264/AVC, get the avc1 box.
    virtual SrsMp4VisualSampleEntry* avc1();
    // For AAC, get the mp4a box.
    virtual SrsMp4AudioSampleEntry* mp4a();
};

/**
 * 8.3.2 Track Header Box (tkhd)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 32
 */
class SrsMp4TrackHeaderBox : public SrsMp4FullBox
{
public:
    // an integer that declares the creation time of the presentation (in seconds since
    // midnight, Jan. 1, 1904, in UTC time)
    uint64_t creation_time;
    // an integer that declares the most recent time the presentation was modified (in
    // seconds since midnight, Jan. 1, 1904, in UTC time)
    uint64_t modification_time;
    // an integer that uniquely identifies this track over the entire life-time of this presentation.
    // Track IDs are never re-used and cannot be zero.
    uint32_t track_ID;
    uint32_t reserved0;
    // an integer that indicates the duration of this track (in the timescale indicated in the Movie
    // Header Box). The value of this field is equal to the sum of the durations of all of the track’s edits. If
    // there is no edit list, then the duration is the sum of the sample durations, converted into the timescale
    // in the Movie Header Box. If the duration of this track cannot be determined then duration is set to all
    // 1s.
    uint64_t duration;
public:
    uint64_t reserved1;
    // specifies the front-to-back ordering of video tracks; tracks with lower numbers are closer to the
    // viewer. 0 is the normal value, and -1 would be in front of track 0, and so on.
    int16_t layer;
    // an integer that specifies a group or collection of tracks. If this field is 0 there is no
    // information on possible relations to other tracks. If this field is not 0, it should be the same for tracks
    // that contain alternate data for one another and different for tracks belonging to different such groups.
    // Only one track within an alternate group should be played or streamed at any one time, and must be
    // distinguishable from other tracks in the group via attributes such as bitrate, codec, language, packet
    // size etc. A group may have only one member.
    int16_t alternate_group;
    // a fixed 8.8 value specifying the track's relative audio volume. Full volume is 1.0 (0x0100) and
    // is the normal value. Its value is irrelevant for a purely visual track. Tracks may be composed by
    // combining them according to their volume, and then using the overall Movie Header Box volume
    // setting; or more complex audio composition (e.g. MPEG-4 BIFS) may be used.
    int16_t volume;
    uint16_t reserved2;
    // a transformation matrix for the video; (u,v,w) are restricted here to (0,0,1), hex (0,0,0x40000000).
    int32_t matrix[9];
    // the track's visual presentation size as fixed-point 16.16 values. These need
    // not be the same as the pixel dimensions of the images, which is documented in the sample
    // description(s); all images in the sequence are scaled to this size, before any overall transformation of
    // the track represented by the matrix. The pixel dimensions of the images are the default values.
    int32_t width;
    int32_t height;
public:
    SrsMp4TrackHeaderBox();
    virtual ~SrsMp4TrackHeaderBox();
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.6.5 Edit Box (edts)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 54
 * An Edit Box maps the presentation time-line to the media time-line as it is stored in the file.
 * The Edit Box is a container for the edit lists.
 */
class SrsMp4EditBox : public SrsMp4Box
{
public:
    SrsMp4EditBox();
    virtual ~SrsMp4EditBox();
};

/**
 * 8.6.6 Edit List Box
 * ISO_IEC_14496-12-base-format-2012.pdf, page 55
 */
struct SrsMp4ElstEntry
{
public:
    // an integer that specifies the duration of this edit segment in units of the timescale
    // in the Movie Header Box
    uint64_t segment_duration;
    // an integer containing the starting time within the media of this edit segment (in media time
    // scale units, in composition time). If this field is set to –1, it is an empty edit. The last edit in a track
    // shall never be an empty edit. Any difference between the duration in the Movie Header Box, and the
    // track’s duration is expressed as an implicit empty edit at the end.
    int64_t media_time;
public:
    // specifies the relative rate at which to play the media corresponding to this edit segment. If this value is 0,
    // then the edit is specifying a ‘dwell’: the media at media-time is presented for the segment-duration. Otherwise
    // this field shall contain the value 1.
    int16_t media_rate_integer;
    int16_t media_rate_fraction;
public:
    SrsMp4ElstEntry();
};

/**
 * 8.6.6 Edit List Box (elst)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 54
 * This box contains an explicit timeline map. Each entry defines part of the track time-line: by mapping part of
 * the media time-line, or by indicating ‘empty’ time, or by defining a ‘dwell’, where a single time-point in the
 * media is held for a period.
 */
class SrsMp4EditListBox : public SrsMp4FullBox
{
public:
    // an integer that gives the number of entries in the following table
    std::vector<SrsMp4ElstEntry> entries;
public:
    SrsMp4EditListBox();
    virtual ~SrsMp4EditListBox();
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.4.1 Media Box (mdia)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 36
 * The media declaration container contains all the objects that declare information about the media data within a
 * track.
 */
class SrsMp4MediaBox : public SrsMp4Box
{
public:
    SrsMp4MediaBox();
    virtual ~SrsMp4MediaBox();
public:
    // Get the type of track, maybe combine of track type,
    // for example, it maybe Audio|Video when contains both.
    // Generally, only single type, no combination.
    virtual SrsMp4TrackType track_type();
    // Get the media header box.
    virtual SrsMp4MediaHeaderBox* mdhd();
    virtual void set_mdhd(SrsMp4MediaHeaderBox* v);
    // Get the hdlr box.
    virtual SrsMp4HandlerReferenceBox* hdlr();
    virtual void set_hdlr(SrsMp4HandlerReferenceBox* v);
    // Get the media info box.
    virtual SrsMp4MediaInformationBox* minf();
    virtual void set_minf(SrsMp4MediaInformationBox* v);
};

/**
 * 8.4.2 Media Header Box (mdhd)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 36
 * The media declaration container contains all the objects that declare information about the media data within a
 * track.
 */
class SrsMp4MediaHeaderBox : public SrsMp4FullBox
{
public:
    // an integer that declares the creation time of the presentation (in seconds since
    // midnight, Jan. 1, 1904, in UTC time)
    uint64_t creation_time;
    // an integer that declares the most recent time the presentation was modified (in
    // seconds since midnight, Jan. 1, 1904, in UTC time)
    uint64_t modification_time;
    // an integer that specifies the time-scale for the entire presentation; this is the number of
    // time units that pass in one second. For example, a time coordinate system that measures time in
    // sixtieths of a second has a time scale of 60.
    uint32_t timescale;
    // an integer that declares length of the presentation (in the indicated timescale). This property
    // is derived from the presentation’s tracks: the value of this field corresponds to the duration of the
    // longest track in the presentation. If the duration cannot be determined then duration is set to all 1s.
    uint64_t duration;
private:
    // the language code for this media. See ISO 639-2/T for the set of three character
    // codes. Each character is packed as the difference between its ASCII value and 0x60. Since the code
    // is confined to being three lower-case letters, these values are strictly positive.
    uint16_t language;
    uint16_t pre_defined;
public:
    SrsMp4MediaHeaderBox();
    virtual ~SrsMp4MediaHeaderBox();
public:
    // the language code for this media. See ISO 639-2/T for the set of three character
    // codes. Each character is packed as the difference between its ASCII value and 0x60. Since the code
    // is confined to being three lower-case letters, these values are strictly positive.
    // @param v The ASCII, for example, 'u'.
    virtual char language0();
    virtual void set_language0(char v);
    // @param v The ASCII, for example, 'n'.
    virtual char language1();
    virtual void set_language1(char v);
    // @param v The ASCII, for example, 'd'.
    virtual char language2();
    virtual void set_language2(char v);
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.4.3 Handler Reference Box (hdlr)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 37
 * This box within a Media Box declares the process by which the media-data in the track is presented, and thus,
 * the nature of the media in a track. For example, a video track would be handled by a video handler.
 */
class SrsMp4HandlerReferenceBox : public SrsMp4FullBox
{
public:
    uint32_t pre_defined;
    // an integer containing one of the following values, or a value from a derived specification:
    //      ‘vide’, Video track
    //      ‘soun’, Audio track
    SrsMp4HandlerType handler_type;
    uint32_t reserved[3];
    // a null-terminated string in UTF-8 characters which gives a human-readable name for the track
    // type (for debugging and inspection purposes).
    std::string name;
public:
    SrsMp4HandlerReferenceBox();
    virtual ~SrsMp4HandlerReferenceBox();
public:
    virtual bool is_video();
    virtual bool is_audio();
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.4.4 Media Information Box (minf)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 38
 * This box contains all the objects that declare characteristic information of the media in the track.
 */
class SrsMp4MediaInformationBox : public SrsMp4Box
{
public:
    SrsMp4MediaInformationBox();
    virtual ~SrsMp4MediaInformationBox();
public:
    // Get the vmhd box.
    virtual SrsMp4VideoMeidaHeaderBox* vmhd();
    virtual void set_vmhd(SrsMp4VideoMeidaHeaderBox* v);
    // Get the smhd box.
    virtual SrsMp4SoundMeidaHeaderBox* smhd();
    virtual void set_smhd(SrsMp4SoundMeidaHeaderBox* v);
    // Get the dinf box.
    virtual SrsMp4DataInformationBox* dinf();
    virtual void set_dinf(SrsMp4DataInformationBox* v);
    // Get the sample table box.
    virtual SrsMp4SampleTableBox* stbl();
    virtual void set_stbl(SrsMp4SampleTableBox* v);
};

/**
 * 8.4.5.2 Video Media Header Box (vmhd)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 38
 * The video media header contains general presentation information, independent of the coding, for video
 * media. Note that the flags field has the value 1.
 */
class SrsMp4VideoMeidaHeaderBox : public SrsMp4FullBox
{
public:
    // a composition mode for this video track, from the following enumerated set,
    // which may be extended by derived specifications:
    //      copy = 0 copy over the existing image
    uint16_t graphicsmode;
    // a set of 3 colour values (red, green, blue) available for use by graphics modes
    uint16_t opcolor[3];
public:
    SrsMp4VideoMeidaHeaderBox();
    virtual ~SrsMp4VideoMeidaHeaderBox();
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.4.5.3 Sound Media Header Box (smhd)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 39
 * The sound media header contains general presentation information, independent of the coding, for audio
 * media. This header is used for all tracks containing audio.
 */
class SrsMp4SoundMeidaHeaderBox : public SrsMp4FullBox
{
public:
    // a fixed-point 8.8 number that places mono audio tracks in a stereo space; 0 is centre (the
    // normal value); full left is -1.0 and full right is 1.0.
    int16_t balance;
    uint16_t reserved;
public:
    SrsMp4SoundMeidaHeaderBox();
    virtual ~SrsMp4SoundMeidaHeaderBox();
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.7.1 Data Information Box (dinf)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 56
 * The data information box contains objects that declare the location of the media information in a track.
 */
class SrsMp4DataInformationBox : public SrsMp4Box
{
public:
    SrsMp4DataInformationBox();
    virtual ~SrsMp4DataInformationBox();
public:
    // Get the dref box.
    virtual SrsMp4DataReferenceBox* dref();
    virtual void set_dref(SrsMp4DataReferenceBox* v);
};

/**
 * 8.7.2 Data Reference Box
 * ISO_IEC_14496-12-base-format-2012.pdf, page 56
 * a 24-bit integer with flags; one flag is defined (x000001) which means that the media
 * data is in the same file as the Movie Box containing this data reference.
 */
class SrsMp4DataEntryBox : public SrsMp4FullBox
{
public:
    std::string location;
public:
    SrsMp4DataEntryBox();
    virtual ~SrsMp4DataEntryBox();
};

/**
 * 8.7.2 Data Reference Box (url )
 * ISO_IEC_14496-12-base-format-2012.pdf, page 56
 */
class SrsMp4DataEntryUrlBox : public SrsMp4DataEntryBox
{
public:
    SrsMp4DataEntryUrlBox();
    virtual ~SrsMp4DataEntryUrlBox();
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.7.2 Data Reference Box (urn )
 * ISO_IEC_14496-12-base-format-2012.pdf, page 56
 */
class SrsMp4DataEntryUrnBox : public SrsMp4DataEntryBox
{
public:
    std::string name;
public:
    SrsMp4DataEntryUrnBox();
    virtual ~SrsMp4DataEntryUrnBox();
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.7.2 Data Reference Box (dref)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 56
 * The data reference object contains a table of data references (normally URLs) that declare the location(s) of
 * the media data used within the presentation. The data reference index in the sample description ties entries
 * in this table to the samples in the track. A track may be split over several sources in this way.
 */
class SrsMp4DataReferenceBox : public SrsMp4FullBox
{
private:
    std::vector<SrsMp4DataEntryBox*> entries;
public:
    SrsMp4DataReferenceBox();
    virtual ~SrsMp4DataReferenceBox();
public:
    virtual uint32_t entry_count();
    virtual SrsMp4DataEntryBox* entry_at(int index);
    virtual SrsMp4DataReferenceBox* append(SrsMp4DataEntryBox* v);
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.5.1 Sample Table Box (stbl)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 40
 * The sample table contains all the time and data indexing of the media samples in a track. Using the tables
 * here, it is possible to locate samples in time, determine their type (e.g. I-frame or not), and determine their
 * size, container, and offset into that container.
 */
class SrsMp4SampleTableBox : public SrsMp4Box
{
public:
    SrsMp4SampleTableBox();
    virtual ~SrsMp4SampleTableBox();
public:
    // Get the sample description box
    virtual SrsMp4SampleDescriptionBox* stsd();
    virtual void set_stsd(SrsMp4SampleDescriptionBox* v);
    // Get the chunk offset box.
    virtual SrsMp4ChunkOffsetBox* stco();
    virtual void set_stco(SrsMp4ChunkOffsetBox* v);
    // Get the sample size box.
    virtual SrsMp4SampleSizeBox* stsz();
    virtual void set_stsz(SrsMp4SampleSizeBox* v);
    // Get the sample to chunk box.
    virtual SrsMp4Sample2ChunkBox* stsc();
    virtual void set_stsc(SrsMp4Sample2ChunkBox* v);
    // Get the dts box.
    virtual SrsMp4DecodingTime2SampleBox* stts();
    virtual void set_stts(SrsMp4DecodingTime2SampleBox* v);
    // Get the cts/pts box.
    virtual SrsMp4CompositionTime2SampleBox* ctts();
    virtual void set_ctts(SrsMp4CompositionTime2SampleBox* v);
    // Get the sync dts box.
    virtual SrsMp4SyncSampleBox* stss();
    virtual void set_stss(SrsMp4SyncSampleBox* v);
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.5.2 Sample Description Box
 * ISO_IEC_14496-12-base-format-2012.pdf, page 43
 */
class SrsMp4SampleEntry : public SrsMp4Box
{
public:
    uint8_t reserved[6];
    // an integer that contains the index of the data reference to use to retrieve
    // data associated with samples that use this sample description. Data references are stored in Data
    // Reference Boxes. The index ranges from 1 to the number of data references.
    uint16_t data_reference_index;
public:
    SrsMp4SampleEntry();
    virtual ~SrsMp4SampleEntry();
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.5.2 Sample Description Box (avc1)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 44
 */
class SrsMp4VisualSampleEntry : public SrsMp4SampleEntry
{
public:
    uint16_t pre_defined0;
    uint16_t reserved0;
    uint32_t pre_defined1[3];
    // the maximum visual width and height of the stream described by this sample
    // description, in pixels
    uint16_t width;
    uint16_t height;
    uint32_t horizresolution;
    uint32_t vertresolution;
    uint32_t reserved1;
    // how many frames of compressed video are stored in each sample. The default is
    // 1, for one frame per sample; it may be more than 1 for multiple frames per sample
    uint16_t frame_count;
    // a name, for informative purposes. It is formatted in a fixed 32-byte field, with the first
    // byte set to the number of bytes to be displayed, followed by that number of bytes of displayable data,
    // and then padding to complete 32 bytes total (including the size byte). The field may be set to 0.
    char compressorname[32];
    // one of the following values
    //      0x0018 – images are in colour with no alpha
    uint16_t depth;
    int16_t pre_defined2;
public:
    SrsMp4VisualSampleEntry();
    virtual ~SrsMp4VisualSampleEntry();
public:
    // For avc1, get the avcc box.
    virtual SrsMp4AvccBox* avcC();
    virtual void set_avcC(SrsMp4AvccBox* v);
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 5.3.4 AVC Video Stream Definition (avcC)
 * ISO_IEC_14496-15-AVC-format-2012.pdf, page 19
 */
class SrsMp4AvccBox : public SrsMp4Box
{
public:
    std::vector<char> avc_config;
public:
    SrsMp4AvccBox();
    virtual ~SrsMp4AvccBox();
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.5.2 Sample Description Box (mp4a)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 45
 */
class SrsMp4AudioSampleEntry : public SrsMp4SampleEntry
{
public:
    uint64_t reserved0;
    uint16_t channelcount;
    uint16_t samplesize;
    uint16_t pre_defined0;
    uint16_t reserved1;
    uint32_t samplerate;
public:
    SrsMp4AudioSampleEntry();
    virtual ~SrsMp4AudioSampleEntry();
public:
    // For AAC codec, get the esds.
    virtual SrsMp4EsdsBox* esds();
    virtual void set_esds(SrsMp4EsdsBox* v);
    // For AAC codec, get the asc.
    virtual SrsMp4DecoderSpecificInfo* asc();
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

// Table 1 — List of Class Tags for Descriptors
// ISO_IEC_14496-1-System-2010.pdf, page 31
enum SrsMp4ESTagEs {
    SrsMp4ESTagESforbidden = 0x00,
    SrsMp4ESTagESObjectDescrTag = 0x01,
    SrsMp4ESTagESInitialObjectDescrTag = 0x02,
    SrsMp4ESTagESDescrTag = 0x03,
    SrsMp4ESTagESDecoderConfigDescrTag = 0x04,
    SrsMp4ESTagESDecSpecificInfoTag = 0x05,
    SrsMp4ESTagESSLConfigDescrTag = 0x06,
    SrsMp4ESTagESExtSLConfigDescrTag = 0x064,
};

/**
 * 7.2.2.2 BaseDescriptor
 * ISO_IEC_14496-1-System-2010.pdf, page 32
 */
class SrsMp4BaseDescriptor : public ISrsCodec
{
public:
    // The values of the class tags are
    // defined in Table 2. As an expandable class the size of each class instance in bytes is encoded and accessible
    // through the instance variable sizeOfInstance (see 8.3.3).
    SrsMp4ESTagEs tag; // bit(8)
    // The decoded or encoded variant length.
    int32_t vlen; // bit(28)
private:
    // The position at buffer to start demux the box.
    int start_pos;
public:
    SrsMp4BaseDescriptor();
    virtual ~SrsMp4BaseDescriptor();
public:
    // Get the left space of box, for decoder.
    virtual int left_space(SrsBuffer* buf);
// Interface ISrsCodec
public:
    virtual int nb_bytes();
    virtual int encode(SrsBuffer* buf);
    virtual int decode(SrsBuffer* buf);
protected:
    virtual int32_t nb_payload() = 0;
    virtual int encode_payload(SrsBuffer* buf) = 0;
    virtual int decode_payload(SrsBuffer* buf) = 0;
};

// Table 5 — objectTypeIndication Values
// ISO_IEC_14496-1-System-2010.pdf, page 49
enum SrsMp4ObjectType
{
    SrsMp4ObjectTypeForbidden = 0x00,
    // Audio ISO/IEC 14496-3
    SrsMp4ObjectTypeAac = 0x40,
};

// Table 6 — streamType Values
// ISO_IEC_14496-1-System-2010.pdf, page 51
enum SrsMp4StreamType
{
    SrsMp4StreamTypeForbidden = 0x00,
    SrsMp4StreamTypeAudioStream = 0x05,
};

/**
 * 7.2.6.7 DecoderSpecificInfo
 * ISO_IEC_14496-1-System-2010.pdf, page 51
 */
class SrsMp4DecoderSpecificInfo : public SrsMp4BaseDescriptor
{
public:
    // AAC Audio Specific Config.
    // 1.6.2.1 AudioSpecificConfig, in ISO_IEC_14496-3-AAC-2001.pdf, page 33.
    std::vector<char> asc;
public:
    SrsMp4DecoderSpecificInfo();
    virtual ~SrsMp4DecoderSpecificInfo();
protected:
    virtual int32_t nb_payload();
    virtual int encode_payload(SrsBuffer* buf);
    virtual int decode_payload(SrsBuffer* buf);
};

/**
 * 7.2.6.6 DecoderConfigDescriptor
 * ISO_IEC_14496-1-System-2010.pdf, page 48
 */
class SrsMp4DecoderConfigDescriptor : public SrsMp4BaseDescriptor
{
public:
    // an indication of the object or scene description type that needs to be supported
    // by the decoder for this elementary stream as per Table 5.
    SrsMp4ObjectType objectTypeIndication; // bit(8)
    SrsMp4StreamType streamType; // bit(6)
    uint8_t upStream; // bit(1)
    uint8_t reserved; // bit(1)
    uint32_t bufferSizeDB; // bit(24)
    uint32_t maxBitrate;
    uint32_t avgBitrate;
    SrsMp4DecoderSpecificInfo* decSpecificInfo; // optional.
public:
    SrsMp4DecoderConfigDescriptor();
    virtual ~SrsMp4DecoderConfigDescriptor();
protected:
    virtual int32_t nb_payload();
    virtual int encode_payload(SrsBuffer* buf);
    virtual int decode_payload(SrsBuffer* buf);
};

/**
 * 7.3.2.3 SL Packet Header Configuration
 * ISO_IEC_14496-1-System-2010.pdf, page 92
 */
class SrsMp4SLConfigDescriptor : public SrsMp4BaseDescriptor
{
public:
    uint8_t predefined;
public:
    SrsMp4SLConfigDescriptor();
    virtual ~SrsMp4SLConfigDescriptor();
protected:
    virtual int32_t nb_payload();
    virtual int encode_payload(SrsBuffer* buf);
    virtual int decode_payload(SrsBuffer* buf);
};

/**
 * 7.2.6.5 ES_Descriptor
 * ISO_IEC_14496-1-System-2010.pdf, page 47
 */
class SrsMp4ES_Descriptor : public SrsMp4BaseDescriptor
{
public:
    uint16_t ES_ID;
    uint8_t streamDependenceFlag; // bit(1)
    uint8_t URL_Flag; // bit(1)
    uint8_t OCRstreamFlag; // bit(1)
    uint8_t streamPriority; // bit(5)
    // if (streamDependenceFlag)
    uint16_t dependsOn_ES_ID;
    // if (URL_Flag)
    std::vector<char> URLstring;
    // if (OCRstreamFlag)
    uint16_t OCR_ES_Id;
    SrsMp4DecoderConfigDescriptor decConfigDescr;
    SrsMp4SLConfigDescriptor slConfigDescr;
public:
    SrsMp4ES_Descriptor();
    virtual ~SrsMp4ES_Descriptor();
protected:
    virtual int32_t nb_payload();
    virtual int encode_payload(SrsBuffer* buf);
    virtual int decode_payload(SrsBuffer* buf);
};

/**
 * 5.6 Sample Description Boxes
 * Elementary Stream Descriptors (esds)
 * ISO_IEC_14496-14-MP4-2003.pdf, page 15
 * @see http://www.mp4ra.org/codecs.html
 */
class SrsMp4EsdsBox : public SrsMp4FullBox
{
public:
    SrsMp4ES_Descriptor* es;
public:
    SrsMp4EsdsBox();
    virtual ~SrsMp4EsdsBox();
public:
    // For AAC codec, get the asc.
    virtual SrsMp4DecoderSpecificInfo* asc();
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.5.2 Sample Description Box (stsd), for Audio/Video.
 * ISO_IEC_14496-12-base-format-2012.pdf, page 40
 * The sample description table gives detailed information about the coding type used, and any initialization
 * information needed for that coding.
 */
class SrsMp4SampleDescriptionBox : public SrsMp4FullBox
{
private:
    std::vector<SrsMp4SampleEntry*> entries;
public:
    SrsMp4SampleDescriptionBox();
    virtual ~SrsMp4SampleDescriptionBox();
public:
    // For H.264/AVC, get the avc1 box.
    virtual SrsMp4VisualSampleEntry* avc1();
    // For AAC, get the mp4a box.
    virtual SrsMp4AudioSampleEntry* mp4a();
public:
    virtual uint32_t entry_count();
    virtual SrsMp4SampleEntry* entrie_at(int index);
    virtual SrsMp4SampleDescriptionBox* append(SrsMp4SampleEntry* v);
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.6.1.2 Decoding Time to Sample Box (stts), for Audio/Video.
 * ISO_IEC_14496-12-base-format-2012.pdf, page 48
 */
struct SrsMp4SttsEntry
{
    // an integer that counts the number of consecutive samples that have the given
    // duration.
    uint32_t sample_count;
    // an integer that gives the delta of these samples in the time-scale of the media.
    uint32_t sample_delta;
    // Constructor
    SrsMp4SttsEntry();
};

/**
 * 8.6.1.2 Decoding Time to Sample Box (stts), for Audio/Video.
 * ISO_IEC_14496-12-base-format-2012.pdf, page 48
 * This box contains a compact version of a table that allows indexing from decoding time to sample number.
 * Other tables give sample sizes and pointers, from the sample number. Each entry in the table gives the
 * number of consecutive samples with the same time delta, and the delta of those samples. By adding the
 * deltas a complete time-to-sample map may be built.
 */
class SrsMp4DecodingTime2SampleBox : public SrsMp4FullBox
{
public:
    // an integer that gives the number of entries in the following table.
    std::vector<SrsMp4SttsEntry> entries;
private:
    // The index for counter to calc the dts for samples.
    uint32_t index;
    uint32_t count;
public:
    SrsMp4DecodingTime2SampleBox();
    virtual ~SrsMp4DecodingTime2SampleBox();
public:
    // Initialize the counter.
    virtual int initialize_counter();
    // When got an sample, index starts from 0.
    virtual int on_sample(uint32_t sample_index, SrsMp4SttsEntry** ppentry);
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.6.1.3 Composition Time to Sample Box (ctts), for Video.
 * ISO_IEC_14496-12-base-format-2012.pdf, page 49
 */
struct SrsMp4CttsEntry
{
    // an integer that counts the number of consecutive samples that have the given offset.
    uint32_t sample_count;
    // uint32_t for version=0
    // int32_t for version=1
    // an integer that gives the offset between CT and DT, such that CT(n) = DT(n) +
    // CTTS(n).
    int64_t sample_offset;
    // Constructor
    SrsMp4CttsEntry();
};

/**
 * 8.6.1.3 Composition Time to Sample Box (ctts), for Video.
 * ISO_IEC_14496-12-base-format-2012.pdf, page 49
 * This box provides the offset between decoding time and composition time. In version 0 of this box the
 * decoding time must be less than the composition time, and the offsets are expressed as unsigned numbers
 * such that CT(n) = DT(n) + CTTS(n) where CTTS(n) is the (uncompressed) table entry for sample n. In version
 * 1 of this box, the composition timeline and the decoding timeline are still derived from each other, but the
 * offsets are signed. It is recommended that for the computed composition timestamps, there is exactly one with
 * the value 0 (zero).
 */
class SrsMp4CompositionTime2SampleBox : public SrsMp4FullBox
{
public:
    // an integer that gives the number of entries in the following table.
    std::vector<SrsMp4CttsEntry> entries;
private:
    // The index for counter to calc the dts for samples.
    uint32_t index;
    uint32_t count;
public:
    SrsMp4CompositionTime2SampleBox();
    virtual ~SrsMp4CompositionTime2SampleBox();
public:
    // Initialize the counter.
    virtual int initialize_counter();
    // When got an sample, index starts from 0.
    virtual int on_sample(uint32_t sample_index, SrsMp4CttsEntry** ppentry);
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.6.2 Sync Sample Box (stss), for Video.
 * ISO_IEC_14496-12-base-format-2012.pdf, page 51
 * This box provides a compact marking of the sync samples within the stream. The table is arranged in strictly
 * increasing order of sample number.
 */
class SrsMp4SyncSampleBox : public SrsMp4FullBox
{
public:
    // an integer that gives the number of entries in the following table. If entry_count is zero,
    // there are no sync samples within the stream and the following table is empty.
    uint32_t entry_count;
    // the numbers of the samples that are sync samples in the stream.
    uint32_t* sample_numbers;
public:
    SrsMp4SyncSampleBox();
    virtual ~SrsMp4SyncSampleBox();
public:
    // Whether the sample is sync, index starts from 0.
    virtual bool is_sync(uint32_t sample_index);
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.7.4 Sample To Chunk Box (stsc), for Audio/Video.
 * ISO_IEC_14496-12-base-format-2012.pdf, page 58
 */
struct SrsMp4StscEntry
{
    // an integer that gives the index of the first chunk in this run of chunks that share the
    // same samples-per-chunk and sample-description-index; the index of the first chunk in a track has the
    // value 1 (the first_chunk field in the first record of this box has the value 1, identifying that the first
    // sample maps to the first chunk).
    uint32_t first_chunk;
    // an integer that gives the number of samples in each of these chunks
    uint32_t samples_per_chunk;
    // an integer that gives the index of the sample entry that describes the
    // samples in this chunk. The index ranges from 1 to the number of sample entries in the Sample
    // Description Box
    uint32_t sample_description_index;
    // Constructor
    SrsMp4StscEntry();
};

/**
 * 8.7.4 Sample To Chunk Box (stsc), for Audio/Video.
 * ISO_IEC_14496-12-base-format-2012.pdf, page 58
 * Samples within the media data are grouped into chunks. Chunks can be of different sizes, and the samples
 * within a chunk can have different sizes. This table can be used to find the chunk that contains a sample,
 * its position, and the associated sample description.
 */
class SrsMp4Sample2ChunkBox : public SrsMp4FullBox
{
public:
    // an integer that gives the number of entries in the following table
    uint32_t entry_count;
    // the numbers of the samples that are sync samples in the stream.
    SrsMp4StscEntry* entries;
private:
    // The index for counter to calc the dts for samples.
    uint32_t index;
public:
    SrsMp4Sample2ChunkBox();
    virtual ~SrsMp4Sample2ChunkBox();
public:
    // Initialize the counter.
    virtual void initialize_counter();
    // When got an chunk, index starts from 0.
    virtual SrsMp4StscEntry* on_chunk(uint32_t chunk_index);
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.7.5 Chunk Offset Box (stco), for Audio/Video.
 * ISO_IEC_14496-12-base-format-2012.pdf, page 59
 * The chunk offset table gives the index of each chunk into the containing file. There are two variants, permitting
 * the use of 32-bit or 64-bit offsets. The latter is useful when managing very large presentations. At most one of
 * these variants will occur in any single instance of a sample table.
 */
class SrsMp4ChunkOffsetBox : public SrsMp4FullBox
{
public:
    // an integer that gives the number of entries in the following table
    uint32_t entry_count;
    // a 32 bit integer that gives the offset of the start of a chunk into its containing
    // media file.
    uint32_t* entries;
public:
    SrsMp4ChunkOffsetBox();
    virtual ~SrsMp4ChunkOffsetBox();
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.7.5 Chunk Large Offset Box (co64), for Audio/Video.
 * ISO_IEC_14496-12-base-format-2012.pdf, page 59
 * The chunk offset table gives the index of each chunk into the containing file. There are two variants, permitting
 * the use of 32-bit or 64-bit offsets. The latter is useful when managing very large presentations. At most one of
 * these variants will occur in any single instance of a sample table.
 */
class SrsMp4ChunkLargeOffsetBox : public SrsMp4FullBox
{
public:
    // an integer that gives the number of entries in the following table
    uint32_t entry_count;
    // a 64 bit integer that gives the offset of the start of a chunk into its containing
    // media file.
    uint64_t* entries;
public:
    SrsMp4ChunkLargeOffsetBox();
    virtual ~SrsMp4ChunkLargeOffsetBox();
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.7.3.2 Sample Size Box (stsz), for Audio/Video.
 * ISO_IEC_14496-12-base-format-2012.pdf, page 58
 * This box contains the sample count and a table giving the size in bytes of each sample. This allows the media data
 * itself to be unframed. The total number of samples in the media is always indicated in the sample count.
 */
class SrsMp4SampleSizeBox : public SrsMp4FullBox
{
public:
    // the default sample size. If all the samples are the same size, this field
    // contains that size value. If this field is set to 0, then the samples have different sizes, and those sizes
    // are stored in the sample size table. If this field is not 0, it specifies the constant sample size, and no
    // array follows.
    uint32_t sample_size;
    // an integer that gives the number of samples in the track; if sample-size is 0, then it is
    // also the number of entries in the following table.
    uint32_t sample_count;
    // each entry_size is an integer specifying the size of a sample, indexed by its number.
    uint32_t* entry_sizes;
public:
    SrsMp4SampleSizeBox();
    virtual ~SrsMp4SampleSizeBox();
public:
    // Get the size of sample.
    virtual int get_sample_size(uint32_t sample_index, uint32_t* psample_size);
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * 8.10.1 User Data Box (udta)
 * ISO_IEC_14496-12-base-format-2012.pdf, page 78
 * This box contains objects that declare user information about the containing box and its data (presentation or
 * track).
 */
class SrsMp4UserDataBox : public SrsMp4Box
{
public:
    std::vector<char> data;
public:
    SrsMp4UserDataBox();
    virtual ~SrsMp4UserDataBox();
protected:
    virtual int nb_header();
    virtual int encode_header(SrsBuffer* buf);
    virtual int decode_header(SrsBuffer* buf);
};

/**
 * Generally, a MP4 sample contains a frame, for example, a video frame or audio frame.
 */
class SrsMp4Sample
{
public:
    // The type of sample, audio or video.
    SrsFrameType type;
    // The offset of sample in file.
    off_t offset;
    // The index of sample with a track, start from 0.
    uint32_t index;
    // The dts in tbn.
    uint64_t dts;
    // For video, the pts in tbn.
    uint64_t pts;
    // The tbn(timebase).
    uint32_t tbn;
    // For video, the frame type, whether keyframe.
    SrsVideoAvcFrameType frame_type;
    // The adjust timestamp in milliseconds.
    // For example, we can adjust a timestamp for A/V to monotonically increase.
    int32_t adjust;
    // The sample data.
    uint32_t nb_data;
    uint8_t* data;
public:
    SrsMp4Sample();
    virtual ~SrsMp4Sample();
public:
    // Get the adjusted dts in ms.
    virtual uint32_t dts_ms();
    // Get the adjusted pts in ms.
    virtual uint32_t pts_ms();
};

/**
 * Build samples from moov, or write samples to moov.
 * One or more sample are grouped to a chunk, each track contains one or more chunks.
 *      The offset of chunk is specified by stco.
 *      The chunk-sample series is speicified by stsc.
 *      The sample size is specified by stsz.
 *      The dts is specified by stts.
 * For video:
 *      The cts/pts is specified by ctts.
 *      The keyframe is specified by stss.
 */
class SrsMp4SampleManager
{
private:
    std::vector<SrsMp4Sample*> samples;
public:
    SrsMp4SampleManager();
    virtual ~SrsMp4SampleManager();
public:
    // Load the samples from moov. There must be atleast one track.
    virtual int load(SrsMp4MovieBox* moov);
    // Get the sample at index position.
    // @remark NULL if exceed the max index.
    virtual SrsMp4Sample* at(uint32_t index);
    // Append the sample to the tail of manager.
    virtual void append(SrsMp4Sample* sample);
    // Write the samples info to moov.
    virtual int write(SrsMp4MovieBox* moov);
private:
    virtual int write_track(SrsFrameType track,
        SrsMp4DecodingTime2SampleBox* stts, SrsMp4SyncSampleBox* stss, SrsMp4CompositionTime2SampleBox* ctts,
        SrsMp4Sample2ChunkBox* stsc, SrsMp4SampleSizeBox* stsz, SrsMp4ChunkOffsetBox* stco);
    virtual int do_load(std::map<uint64_t, SrsMp4Sample*>& tses, SrsMp4MovieBox* moov);
private:
    // Load the samples of track from stco, stsz and stsc.
    // @param tses The temporary samples, key is offset, value is sample.
    // @param tt The type of sample, convert to flv tag type.
    // TODO: Support co64 for stco.
    virtual int load_trak(std::map<uint64_t, SrsMp4Sample*>& tses, SrsFrameType tt,
        SrsMp4MediaHeaderBox* mdhd, SrsMp4ChunkOffsetBox* stco, SrsMp4SampleSizeBox* stsz, SrsMp4Sample2ChunkBox* stsc,
        SrsMp4DecodingTime2SampleBox* stts, SrsMp4CompositionTime2SampleBox* ctts, SrsMp4SyncSampleBox* stss);
};

/**
 * The MP4 demuxer.
 */
class SrsMp4Decoder
{
private:
    // The major brand of decoder, parse from ftyp.
    SrsMp4BoxBrand brand;
    // The samples build from moov.
    SrsMp4SampleManager* samples;
    // The current written sample information.
    uint32_t current_index;
    off_t current_offset;
public:
    // The video codec of first track, generally there is zero or one track.
    // Forbidden if no video stream.
    // TODO: FIXME: Use SrsFormat instead.
    SrsVideoCodecId vcodec;
private:
    // For H.264/AVC, the avcc contains the sps/pps.
    std::vector<char> pavcc;
    // Whether avcc is written to reader.
    bool avcc_written;
public:
    // The audio codec of first track, generally there is zero or one track.
    // Forbidden if no audio stream.
    SrsAudioCodecId acodec;
    // The audio sample rate.
    SrsAudioSampleRate sample_rate;
    // The audio sound bits.
    SrsAudioSampleBits sound_bits;
    // The audio sound type.
    SrsAudioChannels channels;
private:
    // For AAC, the asc in esds box.
    std::vector<char> pasc;
    // Whether asc is written to reader.
    bool asc_written;
private:
    // Underlayer reader and seeker.
    // @remark The demuxer must use seeker for general MP4 to seek the moov.
    ISrsReadSeeker* rsio;
    // The stream used to demux the boxes.
    // TODO: FIXME: refine for performance issue.
    SrsSimpleStream* stream;
    // The temporary buffer to read from buffer.
    char* buf;
public:
    SrsMp4Decoder();
    virtual ~SrsMp4Decoder();
public:
    /**
     * Initialize the decoder with a reader r.
     * @param r The underlayer io reader, user must manage it.
     */
    virtual int initialize(ISrsReadSeeker* rs);
    /**
     * Read a sample from mp4.
     * @param pht The sample hanler type, audio/soun or video/vide.
     * @param pft, The frame type. For video, it's SrsVideoAvcFrameType.
     * @param pct, The codec type. For video, it's SrsVideoAvcFrameTrait. For audio, it's SrsAudioAacFrameTrait.
     * @param pdts The output dts in milliseconds.
     * @param ppts The output pts in milliseconds.
     * @param pnb_sample The output size of payload.
     * @param psample The output payload, user must free it.
     * @remark The decoder will generate the first two audio/video sequence header.
     */
    virtual int read_sample(SrsMp4HandlerType* pht, uint16_t* pft, uint16_t* pct,
        uint32_t* pdts, uint32_t* ppts, uint8_t** psample, uint32_t* pnb_sample);
private:
    virtual int parse_ftyp(SrsMp4FileTypeBox* ftyp);
    virtual int parse_moov(SrsMp4MovieBox* moov);
private:
    // Load the next box from reader.
    // @param required_box_type The box type required, 0 for any box.
    virtual int load_next_box(SrsMp4Box** ppbox, uint32_t required_box_type);
    // @remark Never load the mdat box content, for it's too large.
    virtual int do_load_next_box(SrsMp4Box** ppbox, uint32_t required_box_type);
};

/**
 * The MP4 muxer.
 */
class SrsMp4Encoder
{
private:
    ISrsWriteSeeker* wsio;
    SrsBuffer* buffer;
    // The mdat offset at file, we must update the header when flush.
    off_t mdat_offset;
    // The mdat size in bytes, we must update it to the mdat box header.
    uint64_t mdat_bytes;
    // The samples build from moov.
    SrsMp4SampleManager* samples;
public:
    // The audio codec of first track, generally there is zero or one track.
    // Forbidden if no audio stream.
    SrsAudioCodecId acodec;
    // The audio sample rate.
    SrsAudioSampleRate sample_rate;
    // The audio sound bits.
    SrsAudioSampleBits sound_bits;
    // The audio sound type.
    SrsAudioChannels channels;
private:
    // For AAC, the asc in esds box.
    std::vector<char> pasc;
    // The number of audio samples.
    uint32_t nb_audios;
    // The duration of audio stream.
    uint64_t aduration;
public:
    // The video codec of first track, generally there is zero or one track.
    // Forbidden if no video stream.
    SrsVideoCodecId vcodec;
private:
    // For H.264/AVC, the avcc contains the sps/pps.
    std::vector<char> pavcc;
    // The number of video samples.
    uint32_t nb_videos;
    // The duration of video stream.
    uint64_t vduration;
    // The size width/height of video.
    uint32_t width;
    uint32_t height;
public:
    SrsMp4Encoder();
    virtual ~SrsMp4Encoder();
public:
    // Initialize the encoder with a writer w.
    // @param w The underlayer io writer, user must manage it.
    virtual int initialize(ISrsWriteSeeker* ws);
    // Write a sampel to mp4.
    // @param ht, The sample handler type, audio/soun or video/vide.
    // @param ft, The frame type. For video, it's SrsVideoAvcFrameType.
    // @param ct, The codec type. For video, it's SrsVideoAvcFrameTrait. For audio, it's SrsAudioAacFrameTrait.
    // @param dts The output dts in milliseconds.
    // @param pts The output pts in milliseconds.
    // @param sample The output payload, user must free it.
    // @param nb_sample The output size of payload.
    virtual int write_sample(SrsMp4HandlerType ht, uint16_t ft, uint16_t ct,
        uint32_t dts, uint32_t pts, uint8_t* sample, uint32_t nb_sample);
    // Flush the encoder, to write the moov.
    virtual int flush();
private:
    virtual int copy_sequence_header(bool vsh, uint8_t* sample, uint32_t nb_sample);
    virtual int do_write_sample(SrsMp4Sample* ps, uint8_t* sample, uint32_t nb_sample);
};

#endif

