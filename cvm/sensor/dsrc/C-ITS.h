#ifndef _CVM_SENSOR_DSRC_CITS_H_
#define _CVM_SENSOR_DSRC_CITS_H_

#include <cvm/protocol/BsmData.hpp>
#include <cvm/protocol/MapData.hpp>
#include <cvm/protocol/SpatData.hpp>

namespace cvm
{

namespace sensor
{

namespace dsrc
{

/**
 * @brief This function encodes 'frame_bsm_message' into 'frame_bsm_buffer',
 *        and returns bsm frame message encoded length.
 * @param p_frame_bsm_message
 * @param p_frame_bsm_buffer
 * @param frame_bsm_message_length
 * @return -1 if fail, then encode size
 */
int frame_bsm_encode(const char *p_frame_bsm_message, char *p_frame_bsm_buffer, const int frame_bsm_message_length);


/**
 * @brief This function decodes 'frame_bsm_buffer' into 'frame_bsm_message',
 *        and returns bsm message(need decoded) length.
 * @param p_frame_bsm_message
 * @param p_frame_bsm_buffer
 * @param length
 * @return -1 if fail, then bsm size
 */
int frame_bsm_decode(char *p_frame_bsm_message, const char *p_frame_bsm_buffer, const int length);

/**
 * @brief This function encodes 'p_bsm_message' into p_bsm_buffer,
 *        and returns bsm message encoded length.
 * @param p_bsm_message
 * @param p_bsm_buffer
 * @return -1 if fail, then encode size
 */
int bsmDataEncode_CITS(const cvm::protocol::BsmData& bsmData, char *p_bsm_buffer);

/**
 * @brief This function decodes 'p_bsm_buffer' into 'p_bsm_message',
 *        and returns bsm message decoded length.
 * @param p_bsm_message
 * @param p_bsm_buffer
 * @param length
 * @return -1 if fail, then decode size
 */
int bsmDataDecode_CITS(cvm::protocol::BsmData& bsmData, const char *p_bsm_buffer, const int length);

/**
 * @brief This function decodes 'p_frame_map_buffer' into 'p_frame_map_message'
 * @param p_frame_map_message
 * @param p_frame_map_buffer
 * @param length
 * @return  -1 if fail,then map message(need decoded) length.
 */
int frame_map_decode(char *p_frame_map_message, const char *p_frame_map_buffer, const int length);

/**
 * @brief  * This function decodes 'map_buffer' into 'map_message'
 * @param p_map_message
 * @param p_map_buffer
 * @param length
 * @return -1 if fail, then map message decoded length.
 */
int map_decode(cvm::protocol::MapData *p_map_message, const char *p_map_buffer, const int length);

/**
 * @brief  This function decodes 'p_frame_spat_buffer' into 'p_frame_spat_message'
 * @param p_frame_spat_message
 * @param p_frame_spat_buffer
 * @param length
 * @return -1 if fail, then spat message(need decoded) length.
 */
int frame_spat_decode(char *p_frame_spat_message, const char *p_frame_spat_buffer, const int length);

/**
 * @brief  * This function decodes 'p_spat_buffer' into 'p_spat_message'
 * @param p_spat_message
 * @param p_spat_buffer
 * @param length
 * @return -1 if fail, then spat message decoded length.
 */
int spat_decode(cvm::protocol::SpatData *p_spat_message, const char *p_spat_buffer, const int length);

}

}

}
#endif // _CVM_SENSOR_DSRC_CITS_H_

