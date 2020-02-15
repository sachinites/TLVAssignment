/*
 * =====================================================================================
 *
 *       Filename:  tlv_assignment.c
 *
 *    Description:  This file is an assignment on TLV
 *
 *        Version:  1.0
 *        Created:  02/07/2020 10:59:22 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Er. Abhishek Sagar, Juniper Networks (https://csepracticals.wixsite.com/csepracticals), sachinites@gmail.com
 *        Company:  Juniper Networks
 *
 *        This file is part of the TLV Assignment distribution (https://github.com/sachinites) 
 *        Copyright (c) 2019 Abhishek Sagar.
 *        This program is free software: you can redistribute it and/or modify it under the terms of the GNU General 
 *        Public License as published by the Free Software Foundation, version 3.
 *        
 *        This program is distributed in the hope that it will be useful, but
 *        WITHOUT ANY WARRANTY; without even the implied warranty of
 *        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *        General Public License for more details.
 *
 *        visit website : https://csepracticals.com for more courses and projects
 *                                  
 * =====================================================================================
 */


 /* visit website : https://csepracticals.com */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define TLV_OVERHEAD_SIZE    2

/* Assignment : 
 * Implement the below macros, and use them in function decode_tlv_buffer
 * to decode TLV buffer and its contents*/
#define ITERATE_TLV_BEGIN(start_ptr, type, length, tlv_ptr, buffer_size)    \
    /*Provide macro definition*/



#define ITERATE_TLV_END(start_ptr, type, length, tlv_ptr, buffer_size)  \
    /*Provide macro definition*/

#define NAME_TLV_CODE	    1  // >> String format , Unit Data length 32B
#define WEBSITE_TLV_CODE	2  // >> String format,  Unit Data length 64B
#define EMP_ID_TLV_CODE    	3  // >> Integer format, Unit Data length 8B

static uint8_t
get_unit_data_size(uint8_t tlv_type )
{
    switch(tlv_type){
        case NAME_TLV_CODE:
            return 32;
        case WEBSITE_TLV_CODE:
            return 64;
        case EMP_ID_TLV_CODE:
            return 8;
        default:
            return 0;
    }
}

/*Implement the below function, print all TLVs in the buffer using MACRO definitions*/
void
decode_tlv_buffer(unsigned char *tlv_buffer, 
                  uint32_t tlv_buffer_size){

    uint8_t tlv_type;
    uint8_t tlv_len;
    uint8_t *tlv_value;

    int units = 0, i = 0;

    ITERATE_TLV_BEGIN(tlv_buffer, tlv_type, tlv_len, tlv_value, tlv_buffer_size){
       
        units = tlv_len/get_unit_data_size(tlv_type);

        switch(tlv_type){
            case NAME_TLV_CODE:
            for( i = 0; i < units; i++){
                printf("TLV Type = %d, Name = %s\n", tlv_type,
                    tlv_value + (i * get_unit_data_size(tlv_type)));                
            }
            break;
            case WEBSITE_TLV_CODE:
            for( i = 0; i < units; i++){
                printf("TLV Type = %d, Website Name = %s\n", tlv_type,
                    tlv_value + (i * get_unit_data_size(tlv_type)));                
            }
            break;
            case EMP_ID_TLV_CODE:
            for( i = 0; i < units; i++){
                printf("TLV Type = %d, Emp ID = %lu\n", tlv_type,
                    *(uint64_t *)(tlv_value + (i * get_unit_data_size(tlv_type))));                
            }
            break;
            default:
                ;
        }
    } ITERATE_TLV_END(tlv_buffer, tlv_type, tlv_len, tlv_value, tlv_buffer_size);
}

/*
   +------------------------------------+
   |           tlv_type = 1             |
   +------------------------------------+
   |           tlv_len = 64             |
   +------------------------------------+
   |                                    |
   |          Abhishek Sagar            |
   +------------------------------------+
   |                                    |
   |-         Shivani                   |
   +------------------------------------+
   |           tlv_type = 2             |
   +------------------------------------+
   |           tlv_len = 128            |
   +------------------------------------+
   |                                    |
   |          www.csepracticals.com     |
   +------------------------------------+
   |                                    |
   |          www.facebook.com          |
   +------------------------------------+
   |          tlv_type = 3              |
   +------------------------------------+
   |          tlv_len = 24              |
   +------------------------------------+
   |                                    |
   |          52437                     |
   +------------------------------------+
   |                                    |
   |          52438                     |
   +------------------------------------+
   |                                    |
   |          52439                     |
   +------------------------------------+

*/

/* The below function prepares the tlv buffer in the format
 * as shown in above diagram*/
unsigned char *
prepare_tlv_buffer(uint32_t *total_buffer_size){

    /*Take 222B of TLV buffer*/
    *total_buffer_size = 222;
    unsigned char *tlv_buffer = calloc(1, *total_buffer_size);
    unsigned char *temp = NULL;

    *tlv_buffer = NAME_TLV_CODE;
    *(tlv_buffer + 1) = 64;
    strncpy(tlv_buffer + TLV_OVERHEAD_SIZE, "Abhishek Sagar", 32);
    strncpy(tlv_buffer + TLV_OVERHEAD_SIZE + 32, "Shivani", 32);

    temp = tlv_buffer + TLV_OVERHEAD_SIZE + (32 * 2);

    *temp = WEBSITE_TLV_CODE;
    *(temp + 1) = 128;
    strncpy(temp + TLV_OVERHEAD_SIZE, "www.csepracticals.com", 64);
    strncpy(temp + TLV_OVERHEAD_SIZE + 64, "www.facebook.com", 64);

    temp += TLV_OVERHEAD_SIZE + (64 * 2);

    *temp = EMP_ID_TLV_CODE;
    *(temp + 1) = 24;

    uint64_t *emp_id = (uint64_t *)(temp + TLV_OVERHEAD_SIZE);
    *emp_id = 52437;
    *(emp_id + 1) = 52438;
    *(emp_id + 2) = 52439;
    
    return tlv_buffer;
}

int
main(int argc, char **argv){

    uint32_t total_buffer_size = 0;
    unsigned char *tlv_buffer = prepare_tlv_buffer(&total_buffer_size);
    if(tlv_buffer && total_buffer_size)
        decode_tlv_buffer(tlv_buffer, total_buffer_size);
    return 0;
}
