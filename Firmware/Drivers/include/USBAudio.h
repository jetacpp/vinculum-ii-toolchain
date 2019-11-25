/*
** USBAudio.h
**
** Copyright © 2009-2011 Future Technology Devices International Limited
**
** Header file containing definitions for USB Audio devices.
**
** Author: FTDI
** Project: Vinculum II Drivers
** Module: Vinculum II USB Slave and USB Host Audio Drivers
** Requires:
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef __USBAUDIO_H__
#define __USBAUDIO_H__

// *************************************************************************************************
//
// Definitions taken from USB Device Class Definition for Audio Devices V2.0
//
// *************************************************************************************************

// Table A-8: Audio Class-specific Descriptor Types
//		Descriptor Types											Value
#define USB_DESCRIPTOR_TYPE_AUDIO_UNDEFINED						   0x20 // CS_UNDEFINED
#define USB_DESCRIPTOR_TYPE_AUDIO_DEVICE						   0x21 // CS_DEVICE
#define USB_DESCRIPTOR_TYPE_AUDIO_CONFIGURATION					   0x22 // CS_CONFIGURATION
#define USB_DESCRIPTOR_TYPE_AUDIO_STRING						   0x23 // CS_STRING
#define USB_DESCRIPTOR_TYPE_AUDIO_INTERFACE						   0x24 // CS_INTERFACE
#define USB_DESCRIPTOR_TYPE_AUDIO_ENDPOINT						   0x25 // CS_ENDPOINT

// Table A-9: Audio Class-Specific AC (Audio Control) Interface Descriptor Subtypes
//		Interface Descriptor Subtypes								Value
#define USB_DESCRIPTOR_SUBTYPE_AUDIO_CONTROL_UNDEFINED			   0x00 // AC_DESCRIPTOR_UNDEFINED
#define USB_DESCRIPTOR_SUBTYPE_AUDIO_CONTROL_HEADER				   0x01 // HEADER
#define USB_DESCRIPTOR_SUBTYPE_AUDIO_CONTROL_INPUT_TERMINAL		   0x02 // INPUT_TERMINAL
#define USB_DESCRIPTOR_SUBTYPE_AUDIO_CONTROL_OUTPUT_TERMINAL	   0x03 // OUTPUT_TERMINAL
#define USB_DESCRIPTOR_SUBTYPE_AUDIO_CONTROL_MIXER_UNIT			   0x04 // MIXER_UNIT
#define USB_DESCRIPTOR_SUBTYPE_AUDIO_CONTROL_SELECTOR_UNIT		   0x05 // SELECTOR_UNIT
#define USB_DESCRIPTOR_SUBTYPE_AUDIO_CONTROL_FEATURE_UNIT		   0x06 // FEATURE_UNIT
#define USB_DESCRIPTOR_SUBTYPE_AUDIO_CONTROL_EFFECT_UNIT		   0x07 // EFFECT_UNIT
#define USB_DESCRIPTOR_SUBTYPE_AUDIO_CONTROL_PROCESSING_UNIT	   0x08 // PROCESSING_UNIT
#define USB_DESCRIPTOR_SUBTYPE_AUDIO_CONTROL_EXTENSION_UNIT		   0x09 // EXTENSION_UNIT
#define USB_DESCRIPTOR_SUBTYPE_AUDIO_CONTROL_CLOCK_SOURCE		   0x0A // CLOCK_SOURCE
#define USB_DESCRIPTOR_SUBTYPE_AUDIO_CONTROL_CLOCK_SELECTOR		   0x0B // CLOCK_SELECTOR
#define USB_DESCRIPTOR_SUBTYPE_AUDIO_CONTROL_CLOCK_MULTIPLIER	   0x0C // CLOCK_MULTIPLIER
#define USB_DESCRIPTOR_SUBTYPE_AUDIO_CONTROL_SAMPLE_RATE_CONVERTER 0x0D // SAMPLE_RATE_CONVERTER

// Table A-10: Audio Class-Specific AS (Audio Streaming) Interface Descriptor Subtypes
//		Interface Descriptor Subtypes								Value
#define USB_DESCRIPTOR_SUBTYPE_AUDIO_STREAMING_UNDEFINED		   0x00 // AS_DESCRIPTOR_UNDEFINED
#define USB_DESCRIPTOR_SUBTYPE_AUDIO_STREAMING_GENERAL			   0x01 // AS_GENERAL
#define USB_DESCRIPTOR_SUBTYPE_AUDIO_STREAMING_FORMAT_TYPE		   0x02 // FORMAT_TYPE
#define USB_DESCRIPTOR_SUBTYPE_AUDIO_STREAMING_ENCODER			   0x03 // ENCODER
#define USB_DESCRIPTOR_SUBTYPE_AUDIO_STREAMING_DECODER			   0x04 // DECODER

// Table A-11: Effect Unit Effect Types
//		Audio Effect Type											wEffectType - used with
// usb_audioEffectUnitDescriptor_t
#define USB_AUDIO_EFFECT_UNDEFINED		  0x00 // EFFECT_UNDEFINED
#define USB_AUDIO_EFFECT_PARAM_EQ_SECTION 0x01 // PARAM_EQ_SECTION_EFFECT
#define USB_AUDIO_EFFECT_REVERBERATION	  0x02 // REVERBERATION_EFFECT
#define USB_AUDIO_EFFECT_MOD_DELAY		  0x03 // MOD_DELAY_EFFECT
#define USB_AUDIO_EFFECT_DYN_RANGE_COMP	  0x04 // DYN_RANGE_COMP_EFFECT

// Table A-12: Processing Unit Process Types
//		Audio Process Type											wProcessType - used with
// usb_audioProcessUnitDescriptor_t
#define USB_AUDIO_PROCESS_UNDEFINED						0x00 // PROCESS_UNDEFINED
#define USB_AUDIO_PROCESS_UP_DOWN_MIX					0x01 // UP/DOWNMIX_PROCESS
#define USB_AUDIO_PROCESS_DOLBY_PROLOGIC				0x02 // DOLBY_PROLOGIC_PROCESS
#define USB_AUDIO_PROCESS_STEREO_EXTENDER				0x03 // STEREO_EXTENDER_PROCESS

// Table A-13: Audio Class-Specific Endpoint Descriptor Subtypes
//		Audio Endpoint Subtype										Value
#define USB_ENDPOINT_DESCRIPTOR_AUDIO_UNDEFINED			0x00 // DESCRIPTOR_UNDEFINED
#define USB_ENDPOINT_DESCRIPTOR_AUDIO_GENERAL			0x01 // EP_GENERAL

// Table A-14: Audio Class-Specific Request Codes
//		bRequest													Value
#define USB_REQUEST_CODE_AUDIO_CODE_UNDEFINED			0x00 // REQUEST_CODE_UNDEFINED
#define USB_REQUEST_CODE_AUDIO_CUR						0x01 // CUR
#define USB_REQUEST_CODE_AUDIO_RANGE					0x02 // RANGE
#define USB_REQUEST_CODE_AUDIO_MEM						0x03 // MEM

// Table A-15: Encoder Type Codes
//		Audio Encoder Type											Value
#define USB_AUDIO_ENCODER_TYPE_UNDEFINED				0x00 // ENCODER_UNDEFINED
#define USB_AUDIO_ENCODER_TYPE_OTHER					0x01 // OTHER_ENCODER
#define USB_AUDIO_ENCODER_TYPE_MPEG						0x02 // MPEG_ENCODER
#define USB_AUDIO_ENCODER_TYPE_AC_3						0x03 // AC-3_ENCODER
#define USB_AUDIO_ENCODER_TYPE_WMA						0x04 // WMA_ENCODER
#define USB_AUDIO_ENCODER_TYPE_DTS						0x05 // DTS_ENCODER

// Table A-16: Decoder Type Codes
//		Audio Decoder Type											Value
#define USB_AUDIO_DECODER_TYPE_UNDEFINED				0x00 // DECODER_UNDEFINED
#define USB_AUDIO_DECODER_TYPE_OTHER					0x01 // OTHER_DECODER
#define USB_AUDIO_DECODER_TYPE_MPEG						0x02 // MPEG_DECODER
#define USB_AUDIO_DECODER_TYPE_AC_3						0x03 // AC-3_DECODER
#define USB_AUDIO_DECODER_TYPE_WMA						0x04 // WMA_DECODER
#define USB_AUDIO_DECODER_TYPE_DTS						0x05 // DTS_DECODER

// Table A-17: Clock Source Control Selectors
//		Control Selector											Value
#define USB_AUDIO_CLOCK_SOURCE_UNDEFINED				0x00 // CS_CONTROL_UNDEFINED
#define USB_AUDIO_CLOCK_SOURCE_SAM_FREQ					0x01 // CS_SAM_FREQ_CONTROL
#define USB_AUDIO_CLOCK_SOURCE_CLOCK_VALID				0x02 // CS_CLOCK_VALID_CONTROL

// Table A-18: Clock Selector Control Selectors
//		Control Selector											Value
#define USB_AUDIO_CLOCK_SELECTOR_UNDEFINFED				0x00 // CX_CONTROL_UNDEFINED
#define USB_AUDIO_CLOCK_SELECTOR_CONTROL				0x01 // CX_CLOCK_SELECTOR_CONTROL

// Table A-19: Clock Multiplier Control Selectors
//		Control Selector											Value
#define USB_AUDIO_CLOCK_MULTIPLIER_UNDEFINED			0x00 // CM_CONTROL_UNDEFINED
#define USB_AUDIO_CLOCK_MULTIPLIER_NUMERATOR			0x01 // CM_NUMERATOR_CONTROL
#define USB_AUDIO_CLOCK_MULTIPLIER_DENOMINATOR			0x02 // CM_DENOMINATOR_CONTROL

// Table A-20: Terminal Control Selectors
//		Control Selector											Value
#define USB_AUDIO_TERMINAL_UNDEFINED					0x00 // TE_CONTROL_UNDEFINED
#define USB_AUDIO_TERMINAL_COPY_PROTECT					0x01 // TE_COPY_PROTECT_CONTROL
#define USB_AUDIO_TERMINAL_CONNECTOR					0x02 // TE_CONNECTOR_CONTROL
#define USB_AUDIO_TERMINAL_OVERLOAD						0x03 // TE_OVERLOAD_CONTROL
#define USB_AUDIO_TERMINAL_CLUSTER						0x04 // TE_CLUSTER_CONTROL
#define USB_AUDIO_TERMINAL_UNDERFLOW					0x05 // TE_UNDERFLOW_CONTROL
#define USB_AUDIO_TERMINAL_OVERFLOW						0x06 // TE_OVERFLOW_CONTROL
#define USB_AUDIO_TERMINAL_LATENCY						0x07 // TE_LATENCY_CONTROL

// Table A-21: Mixer Control Selectors
//		Control Selector											Value
#define USB_AUDIO_MIXER_UNDEFINED						0x00 // MU_CONTROL_UNDEFINED
#define USB_AUDIO_MIXER_MIXER_CONTROL					0x01 // MU_MIXER_CONTROL
#define USB_AUDIO_MIXER_CLUSTER							0x02 // MU_CLUSTER_CONTROL
#define USB_AUDIO_MIXER_UNDERFLOW						0x03 // MU_UNDERFLOW_CONTROL
#define USB_AUDIO_MIXER_OVERFLOW						0x04 // MU_OVERFLOW_CONTROL
#define USB_AUDIO_MIXER_LATENCY							0x05 // MU_LATENCY_CONTROL

// Table A-22: Selector Control Selectors
//		Control Selector											Value
#define USB_AUDIO_SELECTOR_UNDEFINED					0x00 // SU_CONTROL_UNDEFINED
#define USB_AUDIO_SELECTOR_SELECTOR_CONTROL				0x01 // SU_SELECTOR_CONTROL
#define USB_AUDIO_SELECTOR_LATENCY						0x02 // SU_LATENCY_CONTROL

// Table A-23: Feature Unit Control Selectors
//		Control Selector											Value
#define USB_AUDIO_FEATURE_UNIT_UNDEFINED				0x00 // FU_CONTROL_UNDEFINED
#define USB_AUDIO_FEATURE_UNIT_MUTE						0x01 // FU_MUTE_CONTROL
#define USB_AUDIO_FEATURE_UNIT_VOLUME					0x02 // FU_VOLUME_CONTROL
#define USB_AUDIO_FEATURE_UNIT_BASS						0x03 // FU_BASS_CONTROL
#define USB_AUDIO_FEATURE_UNIT_MID						0x04 // FU_MID_CONTROL
#define USB_AUDIO_FEATURE_UNIT_TREBLE					0x05 // FU_TREBLE_CONTROL
#define USB_AUDIO_FEATURE_UNIT_GRAPHIC_EQUALIZER		0x06 // FU_GRAPHIC_EQUALIZER_CONTROL
#define USB_AUDIO_FEATURE_UNIT_AUTOMATIC_GAIN			0x07 // FU_AUTOMATIC_GAIN_CONTROL
#define USB_AUDIO_FEATURE_UNIT_DELAY					0x08 // FU_DELAY_CONTROL
#define USB_AUDIO_FEATURE_UNIT_BASS_BOOST				0x09 // FU_BASS_BOOST_CONTROL
#define USB_AUDIO_FEATURE_UNIT_LOUDNESS					0x0A // FU_LOUDNESS_CONTROL
#define USB_AUDIO_FEATURE_UNIT_INPUT_GAIN				0x0B // FU_INPUT_GAIN_CONTROL
#define USB_AUDIO_FEATURE_UNIT_INPUT_GAIN_PAD			0x0C // FU_INPUT_GAIN_PAD_CONTROL
#define USB_AUDIO_FEATURE_UNIT_PHASE_INVERTER			0x0D // FU_PHASE_INVERTER_CONTROL
#define USB_AUDIO_FEATURE_UNIT_UNDERFLOW				0x0E // FU_UNDERFLOW_CONTROL
#define USB_AUDIO_FEATURE_UNIT_OVERFLOW					0x0F // FU_OVERFLOW_CONTROL
#define USB_AUDIO_FEATURE_UNIT_LATENCY					0x10 // FU_LATENCY_CONTROL

// Table A-24: Parametric Equalizer Section Effect Unit Control Selectors
//		Control Selector											Value
#define USB_AUDIO_EFFECT_EQUALIZER_UNDEFINED			0x00 // PE_CONTROL_UNDEFINED
#define USB_AUDIO_EFFECT_EQUALIZER_ENABLE				0x01 // PE_ENABLE_CONTROL
#define USB_AUDIO_EFFECT_EQUALIZER_CENTERFREQ			0x02 // PE_CENTERFREQ_CONTROL
#define USB_AUDIO_EFFECT_EQUALIZER_QFACTOR				0x03 // PE_QFACTOR_CONTROL
#define USB_AUDIO_EFFECT_EQUALIZER_GAIN					0x04 // PE_GAIN_CONTROL
#define USB_AUDIO_EFFECT_EQUALIZER_UNDERFLOW			0x05 // PE_UNDERFLOW_CONTROL
#define USB_AUDIO_EFFECT_EQUALIZER_OVERFLOW				0x06 // PE_OVERFLOW_CONTROL
#define USB_AUDIO_EFFECT_EQUALIZER_LATENCY				0x07 // PE_LATENCY_CONTROL

// Table A-25: Reverberation Effect Unit Control Selectors
//		Control Selector											Value
#define USB_AUDIO_EFFECT_REVERB_UNDEFINED				0x00 // RV_CONTROL_UNDEFINED
#define USB_AUDIO_EFFECT_REVERB_ENABLE					0x01 // RV_ENABLE_CONTROL
#define USB_AUDIO_EFFECT_REVERB_TYPE					0x02 // RV_TYPE_CONTROL
#define USB_AUDIO_EFFECT_REVERB_LEVEL					0x03 // RV_LEVEL_CONTROL
#define USB_AUDIO_EFFECT_REVERB_TIME					0x04 // RV_TIME_CONTROL
#define USB_AUDIO_EFFECT_REVERB_FEEDBACK				0x05 // RV_FEEDBACK_CONTROL
#define USB_AUDIO_EFFECT_REVERB_PREDELAY				0x06 // RV_PREDELAY_CONTROL
#define USB_AUDIO_EFFECT_REVERB_DENSITY					0x07 // RV_DENSITY_CONTROL
#define USB_AUDIO_EFFECT_REVERB_HIFREQ_ROLLOFF			0x08 // RV_HIFREQ_ROLLOFF_CONTROL
#define USB_AUDIO_EFFECT_REVERB_UNDERFLOW				0x09 // RV_UNDERFLOW_CONTROL
#define USB_AUDIO_EFFECT_REVERB_OVERFLOW				0x0A // RV_OVERFLOW_CONTROL
#define USB_AUDIO_EFFECT_REVERB_LATENCY					0x0B // RV_LATENCY_CONTROL

// Table A-26: Modulation Delay Effect Unit Control Selectors
//		Control Selector											Value
#define USB_AUDIO_EFFECT_MODULATION_UNDEFINED			0x00 // MD_CONTROL_UNDEFINED
#define USB_AUDIO_EFFECT_MODULATION_ENABLE				0x01 // MD_ENABLE_CONTROL
#define USB_AUDIO_EFFECT_MODULATION_BALANCE				0x02 // MD_BALANCE_CONTROL
#define USB_AUDIO_EFFECT_MODULATION_RATE				0x03 // MD_RATE_CONTROL
#define USB_AUDIO_EFFECT_MODULATION_DEPTH				0x04 // MD_DEPTH_CONTROL
#define USB_AUDIO_EFFECT_MODULATION_TIME				0x05 // MD_TIME_CONTROL
#define USB_AUDIO_EFFECT_MODULATION_FEEDBACK			0x06 // MD_FEEDBACK_CONTROL
#define USB_AUDIO_EFFECT_MODULATION_UNDERFLOW			0x07 // MD_UNDERFLOW_CONTROL
#define USB_AUDIO_EFFECT_MODULATION_OVERFLOW			0x08 // MD_OVERFLOW_CONTROL
#define USB_AUDIO_EFFECT_MODULATION_LATENCY				0x09 // MD_LATENCY_CONTROL

// Table A-27: Dynamic Range Compressor Effect Unit Control Selectors
//		Control Selector											Value
#define USB_AUDIO_EFFECT_DYNAMIC_RANGE_UNDEFINED		0x00 // DR_CONTROL_UNDEFINED
#define USB_AUDIO_EFFECT_DYNAMIC_RANGE_ENABLE			0x01 // DR_ENABLE_CONTROL
#define USB_AUDIO_EFFECT_DYNAMIC_RANGE_COMPRESSION_RATE 0x02 // DR_COMPRESSION_RATE_CONTROL
#define USB_AUDIO_EFFECT_DYNAMIC_RANGE_MAXAMPL			0x03 // DR_MAXAMPL_CONTROL
#define USB_AUDIO_EFFECT_DYNAMIC_RANGE_THRESHOLD		0x04 // DR_THRESHOLD_CONTROL
#define USB_AUDIO_EFFECT_DYNAMIC_RANGE_ATTACK_TIME		0x05 // DR_ATTACK_TIME_CONTROL
#define USB_AUDIO_EFFECT_DYNAMIC_RANGE_RELEASE_TIME		0x06 // DR_RELEASE_TIME_CONTROL
#define USB_AUDIO_EFFECT_DYNAMIC_RANGE_UNDERFLOW		0x07 // DR_UNDERFLOW_CONTROL
#define USB_AUDIO_EFFECT_DYNAMIC_RANGE_OVERFLOW			0x08 // DR_OVERFLOW_CONTROL
#define USB_AUDIO_EFFECT_DYNAMIC_RANGE_LATENCY			0x09 // DR_LATENCY_CONTROL

// Table A-28: Up/Down-mix Processing Unit Control Selectors
//		Control Selector											Value
#define USB_AUDIO_PROCESS_UP_DOWN_MIX_UNDEFINED			0x00 // UD_CONTROL_UNDEFINED
#define USB_AUDIO_PROCESS_UP_DOWN_MIX_ENABLE			0x01 // UD_ENABLE_CONTROL
#define USB_AUDIO_PROCESS_UP_DOWN_MIX_MODE_SELECT		0x02 // UD_MODE_SELECT_CONTROL
#define USB_AUDIO_PROCESS_UP_DOWN_MIX_CLUSTER			0x03 // UD_CLUSTER_CONTROL
#define USB_AUDIO_PROCESS_UP_DOWN_MIX_UNDERFLOW			0x04 // UD_UNDERFLOW_CONTROL
#define USB_AUDIO_PROCESS_UP_DOWN_MIX_OVERFLOW			0x05 // UD_OVERFLOW_CONTROL
#define USB_AUDIO_PROCESS_UP_DOWN_MIX_LATENCY			0x06 // UD_LATENCY_CONTROL

// Table A-29: Dolby Prologic Processing Unit Control Selectors
//		Control Selector											Value
#define USB_AUDIO_PROCESS_DOLBY_PROLOGIC_UNDEFINED		0x00 // DP_CONTROL_UNDEFINED
#define USB_AUDIO_PROCESS_DOLBY_PROLOGIC_ENABLE			0x01 // DP_ENABLE_CONTROL
#define USB_AUDIO_PROCESS_DOLBY_PROLOGIC_MODE_SELECT	0x02 // DP_MODE_SELECT_CONTROL
#define USB_AUDIO_PROCESS_DOLBY_PROLOGIC_CLUSTER		0x03 // DP_CLUSTER_CONTROL
#define USB_AUDIO_PROCESS_DOLBY_PROLOGIC_UNDERFLOW		0x04 // DP_UNDERFLOW_CONTROL
#define USB_AUDIO_PROCESS_DOLBY_PROLOGIC_OVERFLOW		0x05 // DP_OVERFLOW_CONTROL
#define USB_AUDIO_PROCESS_DOLBY_PROLOGIC_LATENCY		0x06 // DP_LATENCY_CONTROL

// Table A-30: Stereo Extender Processing Unit Control Selectors
//		Control Selector											Value
#define USB_AUDIO_STEREO_EXTENDER_UNDEFINED				0x00 // ST_EXT_CONTROL_UNDEFINED
#define USB_AUDIO_STEREO_EXTENDER_ENABLE				0x01 // ST_EXT_ENABLE_CONTROL
#define USB_AUDIO_STEREO_EXTENDER_WIDTH					0x02 // ST_EXT_WIDTH_CONTROL
#define USB_AUDIO_STEREO_EXTENDER_UNDERFLOW				0x03 // ST_EXT_UNDERFLOW_CONTROL
#define USB_AUDIO_STEREO_EXTENDER_OVERFLOW				0x04 // ST_EXT_OVERFLOW_CONTROL
#define USB_AUDIO_STEREO_EXTENDER_LATENCY				0x05 // ST_EXT_LATENCY_CONTROL

// Table A-31: Extension Unit Control Selectors
//		Control Selector											Value
#define USB_AUDIO_EXTENSION_UNIT_UNDEFINED				0x00 // XU_CONTROL_UNDEFINED
#define USB_AUDIO_EXTENSION_UNIT_ENABLE					0x01 // XU_ENABLE_CONTROL
#define USB_AUDIO_EXTENSION_UNIT_CLUSTER				0x02 // XU_CLUSTER_CONTROL
#define USB_AUDIO_EXTENSION_UNIT_UNDERFLOW				0x03 // XU_UNDERFLOW_CONTROL
#define USB_AUDIO_EXTENSION_UNIT_OVERFLOW				0x04 // XU_OVERFLOW_CONTROL
#define USB_AUDIO_EXTENSION_UNIT_LATENCY				0x05 // XU_LATENCY_CONTROL

// Table A-32: AudioStreaming Interface Control Selectors
//		Control Selector											Value
#define USB_AUDIO_STREAMING_UNDEFINED					0x00 // AS_CONTROL_UNDEFINED
#define USB_AUDIO_STREAMING_ACT_ALT_SETTING				0x01 // AS_ACT_ALT_SETTING_CONTROL
#define USB_AUDIO_STREAMING_VAL_ALT_SETTINGS			0x02 // AS_VAL_ALT_SETTINGS_CONTROL
#define USB_AUDIO_STREAMING_AUDIO_DATA_FORMAT			0x03 // AS_AUDIO_DATA_FORMAT_CONTROL

// Table A-33: Encoder Control Selectors
//		Control Selector											Value
#define USB_AUDIO_ENCODER_UNDEFINED						0x00 // EN_CONTROL_UNDEFINED
#define USB_AUDIO_ENCODER_BIT_RATE						0x01 // EN_BIT_RATE_CONTROL
#define USB_AUDIO_ENCODER_QUALITY						0x02 // EN_QUALITY_CONTROL
#define USB_AUDIO_ENCODER_VBR							0x03 // EN_VBR_CONTROL
#define USB_AUDIO_ENCODER_TYPE							0x04 // EN_TYPE_CONTROL
#define USB_AUDIO_ENCODER_UNDERFLOW						0x05 // EN_UNDERFLOW_CONTROL
#define USB_AUDIO_ENCODER_OVERFLOW						0x06 // EN_OVERFLOW_CONTROL
#define USB_AUDIO_ENCODER_ENCODER_ERROR					0x07 // EN_ENCODER_ERROR_CONTROL
#define USB_AUDIO_ENCODER_PARAM1						0x08 // EN_PARAM1_CONTROL
#define USB_AUDIO_ENCODER_PARAM2						0x09 // EN_PARAM2_CONTROL
#define USB_AUDIO_ENCODER_PARAM3						0x0A // EN_PARAM3_CONTROL
#define USB_AUDIO_ENCODER_PARAM4						0x0B // EN_PARAM4_CONTROL
#define USB_AUDIO_ENCODER_PARAM5						0x0C // EN_PARAM5_CONTROL
#define USB_AUDIO_ENCODER_PARAM6						0x0D // EN_PARAM6_CONTROL
#define USB_AUDIO_ENCODER_PARAM7						0x0E // EN_PARAM7_CONTROL
#define USB_AUDIO_ENCODER_PARAM8						0x0F // EN_PARAM8_CONTROL

// Table A-34: MPEG Decoder Control Selectors
//		Control Selector											Value
#define USB_AUDIO_DECODER_MPEG_UNDEFINED				0x00 // MD_CONTROL_UNDEFINED
#define USB_AUDIO_DECODER_MPEG_DUAL_CHANNEL				0x01 // MD_DUAL_CHANNEL_CONTROL
#define USB_AUDIO_DECODER_MPEG_SECOND_STEREO			0x02 // MD_SECOND_STEREO_CONTROL
#define USB_AUDIO_DECODER_MPEG_MULTILINGUAL				0x03 // MD_MULTILINGUAL_CONTROL
#define USB_AUDIO_DECODER_MPEG_DYN_RANGE				0x04 // MD_DYN_RANGE_CONTROL
#define USB_AUDIO_DECODER_MPEG_SCALING					0x05 // MD_SCALING_CONTROL
#define USB_AUDIO_DECODER_MPEG_HILO_SCALING				0x06 // MD_HILO_SCALING_CONTROL
#define USB_AUDIO_DECODER_MPEG_UNDERFLOW				0x07 // MD_UNDERFLOW_CONTROL
#define USB_AUDIO_DECODER_MPEG_OVERFLOW					0x08 // MD_OVERFLOW_CONTROL
#define USB_AUDIO_DECODER_MPEG_DECODER_ERROR			0x09 // MD_DECODER_ERROR_CONTROL

// Table A-35: AC-3 Decoder Control Selectors
//		Control Selector											Value
#define USB_AUDIO_DECODER_AC_3_UNDEFINED				0x00 // AD_CONTROL_UNDEFINED
#define USB_AUDIO_DECODER_AC_3_MODE						0x01 // AD_MODE_CONTROL
#define USB_AUDIO_DECODER_AC_3_DYN_RANGE				0x02 // AD_DYN_RANGE_CONTROL
#define USB_AUDIO_DECODER_AC_3_SCALING					0x03 // AD_SCALING_CONTROL
#define USB_AUDIO_DECODER_AC_3_HILO_SCALING				0x04 // AD_HILO_SCALING_CONTROL
#define USB_AUDIO_DECODER_AC_3_UNDERFLOW				0x05 // AD_UNDERFLOW_CONTROL
#define USB_AUDIO_DECODER_AC_3_OVERFLOW					0x06 // AD_OVERFLOW_CONTROL
#define USB_AUDIO_DECODER_AC_3_DECODER_ERROR			0x07 // AD_DECODER_ERROR_CONTROL

// Table A-36: WMA Decoder Control Selectors
//		Control Selector											Value
#define USB_AUDIO_DECODER_WMA_UNDEFINED					0x00 // WD_CONTROL_UNDEFINED
#define USB_AUDIO_DECODER_WMA_UNDERFLOW					0x01 // WD_UNDERFLOW_CONTROL
#define USB_AUDIO_DECODER_WMA_OVERFLOW					0x02 // WD_OVERFLOW_CONTROL
#define USB_AUDIO_DECODER_WMA_DECODER_ERROR				0x03 // WD_DECODER_ERROR_CONTROL

// Table A-37: DTS Decoder Control Selectors
//		Control Selector											Value
#define USB_AUDIO_DECODER_DTS_UNDEFINED					0x00 // DD_CONTROL_UNDEFINED
#define USB_AUDIO_DECODER_DTS_UNDERFLOW					0x01 // DD_UNDERFLOW_CONTROL
#define USB_AUDIO_DECODER_DTS_OVERFLOW					0x02 // DD_OVERFLOW_CONTROL
#define USB_AUDIO_DECODER_DTS_DECODER_ERROR				0x03 // DD_DECODER_ERROR_CONTROL

// Table A-38: Endpoint Control Selectors
//		Control Selector											Value
#define USB_AUDIO_ENDPOINT_UNDEFINED					0x00 // EP_CONTROL_UNDEFINED
#define USB_AUDIO_ENDPOINT_PITCH						0x01 // EP_PITCH_CONTROL
#define USB_AUDIO_ENDPOINT_DATA_OVERRUN					0x02 // EP_DATA_OVERRUN_CONTROL
#define USB_AUDIO_ENDPOINT_DATA_UNDERRUN				0x03 // EP_DATA_UNDERRUN_CONTROL

// Table 4-1: Audio Channel Cluster Descriptor
typedef struct _usb_audioChannelClusterDescriptor_t
{
    unsigned char bNrChannels;
    unsigned long bmChannelConfig;
    unsigned char iChannelNames;
} usb_audioChannelClusterDescriptor_t;

// Table 4-3: Standard Interface Association Descriptor
typedef struct _usb_audioInterfaceAssociationDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bFirstInterface;
    unsigned char bInterfaceCount;
    unsigned char bFunctionClass;
    unsigned char bFunctionSubClass;
    unsigned char bFunctionProtocol;
    unsigned char iFunction;
} usb_audioInterfaceAssociationDescriptor_t;

// Table 4-4: Standard AC Interface Descriptor
typedef struct _usb_audioControlInterfaceDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bInterfaceNumber;
    unsigned char bAlternateSetting;
    unsigned char bNumEndpoints;
    unsigned char bInterfaceClass;
    unsigned char bInterfaceSubClass;
    unsigned char bInterfaceProtocol;
    unsigned char iInterface;
} usb_audioControlInterfaceDescriptor_t;

// Table 4-5: Class-Specific AC Interface Header Descriptor
typedef struct _usb_audioControlInterfaceHeaderDescriptor_t
{
    unsigned char  bLength;
    unsigned char  bDescriptorType;
    unsigned char  bDescriptorSubtype;
    unsigned short bcdADC;
    unsigned char  bCategory;
    unsigned short wTotalLength;
    unsigned char  bmControls;
} usb_audioControlInterfaceHeaderDescriptor_t;

// Table 4-6: Clock Source Descriptor
typedef struct _usb_audioClockSourceDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bClockID;
    unsigned char bmAttributes;
    unsigned char bmControls;
    unsigned char bAssocTerminal;
    unsigned char iClockSource;
} usb_audioClockSourceDescriptor_t;

// Table 4-7: Clock Selector Descriptor
typedef struct _usb_audioClockSelectorDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bClockID;
    unsigned char bNrInPins;
    unsigned char baCSourceID1;
    // unsigned char baCSourceID2;
    // ...
    // unsigned char baCSourceIDp;
    unsigned char bmControls;
    unsigned char iClockSelector;
} usb_audioClockSelectorDescriptor_t;

// Table 4-8: Clock Multiplier Descriptor
typedef struct _usb_audioClockMultiplierDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bClockID;
    unsigned char bCSourceID;
    unsigned char bmControls;
    unsigned char iClockMultiplier;
} usb_audioClockMultiplierDescriptor_t;

// Table 4-9: Input Terminal Descriptor
typedef struct _usb_audioInputTerminalDescriptor_t
{
    unsigned char  bLength;
    unsigned char  bDescriptorType;
    unsigned char  bDescriptorSubtype;
    unsigned char  bTerminalID;
    unsigned short wTerminalType;
    unsigned char  bAssocTerminal;
    unsigned char  bCSourceID;
    unsigned char  bNrChannels;
    unsigned long  bmChannelConfig;
    unsigned char  iChannelNames;
    unsigned short bmControls;
    unsigned char  iTerminal;
} usb_audioInputTerminalDescriptor_t;

// Table 4-10: Output Terminal Descriptor
typedef struct _usb_audioOutputTerminalDescriptor_t
{
    unsigned char  bLength;
    unsigned char  bDescriptorType;
    unsigned char  bDescriptorSubtype;
    unsigned char  bTerminalID;
    unsigned short wTerminalType;
    unsigned char  bAssocTerminal;
    unsigned char  bSourceID;
    unsigned char  bCSourceID;
    unsigned short bmControls;
    unsigned char  iTerminal;
} usb_audioOutputTerminalDescriptor_t;

// Table 4-11: Mixer Unit Descriptor
typedef struct _usb_audioMixerUnitDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bUnitID;
    unsigned char bNrInPins;
    unsigned char baSourceID1;
    // unsigned char baSourceID2;
    // ...
    // unsigned char baSourceIDp;
    unsigned char bNrChannels;
    unsigned long bmChannelConfig;
    unsigned char iChannelNames;
    unsigned long bmMixerControls;     // NOTE: can be char, short or long
    unsigned char bmControls;
    unsigned char iMixer;
} usb_audioMixerUnitDescriptor_t;

// Table 4-12: Selector Unit Descriptor
typedef struct _usb_audioSelectorUnitDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bUnitID;
    unsigned char bNrInPins;
    unsigned char baSourceID1;
    // unsigned char baSourceID2;
    // ...
    // unsigned char baSourceIDp;
    unsigned char bmControls;
    unsigned char iSelector;
} usb_audioSelectorUnitDescriptor_t;

// Table 4-13: Feature Unit Descriptor
typedef struct _usb_audioFeatureUnitDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bUnitID;
    unsigned char bSourceID;
    unsigned long bmaControls0;
    unsigned long bmaControls1;
    //	...;
    //	unsigned long bmaControlsch;
    unsigned char iFeature;
} usb_audioFeatureUnitDescriptor_t;

// Table 4-14: Sampling Rate Converter Unit Descriptor
typedef struct _usb_audioSamplingRateConverterUnitDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bUnitID;
    unsigned char bSourceID;
    unsigned char bCSourceInID;
    unsigned char bCSourceOutID;
    unsigned char iSRC;
} usb_audioSamplingRateConverterUnitDescriptor_t;

// Table 4-15: Common Part of the Effect Unit Descriptor
// Also applies to...
// Table 4-16: Parametric Equalizer Section Effect Unit Descriptor
// Table 4-17: Reverberation Effect Unit Descriptor
// Table 4-18: Modulation Delay Effect Unit Descriptor
// Table 4-19: Dynamic Range Compressor Effect Unit Descriptor
typedef struct _usb_audioEffectUnitDescriptor_t
{
    unsigned char  bLength;
    unsigned char  bDescriptorType;
    unsigned char  bDescriptorSubtype;
    unsigned char  bUnitID;
    unsigned short wEffectType;
    unsigned char  bSourceID;
    unsigned long  bmaControls0;
    unsigned long  bmaControls1;
    //	...;
    //	unsigned long bmaControlsch;
    unsigned char  iEffects;
} usb_audioEffectUnitDescriptor_t;

// Table 4-20: Common Part of the Processing Unit Descriptor
// Also applies to...
// Table 4-21: Up/Down-mix Processing Unit Descriptor
// Table 4-22: Dolby Prologic Processing Unit Descriptor
// Table 4-23: Stereo Extender Processing Unit Descriptor
typedef struct _usb_audioProcessUnitDescriptor_t
{
    unsigned char  bLength;
    unsigned char  bDescriptorType;
    unsigned char  bDescriptorSubtype;
    unsigned char  bUnitID;
    unsigned short wProcessType;
    unsigned char  bNrInPins;
    unsigned char  baSourceID1;
    //	...;
    //	unsigned char baSourceIDp;
    unsigned char  bNrChannels;
    unsigned long  bmChannelConfig;
    unsigned char  iChannelNames;
    unsigned short bmControls;
    unsigned char  iProcessing;
    // process specific descriptor appended here...
} usb_audioProcessUnitDescriptor_t;

// Table 4-24: Extension Unit Descriptor
typedef struct _usb_audioExtensionUnitDescriptor_t
{
    unsigned char  bLength;
    unsigned char  bDescriptorType;
    unsigned char  bDescriptorSubtype;
    unsigned char  bUnitID;
    unsigned short wExtensionCode;
    unsigned char  bNrInPins;
    unsigned char  baSourceID1;
    //	...;
    //	unsigned char baSourceIDp;
    unsigned char  bNrChannels;
    unsigned long  bmChannelConfig;
    unsigned char  iChannelNames;
    unsigned char  bmControls;
    unsigned char  iExtension;
} usb_audioExtensionUnitDescriptor_t;

// Table 4-25: Standard Audio Control (AC) Interrupt Endpoint Descriptor
typedef struct _usb_audioControlInterruptEndpointDescriptor_t
{
    unsigned char  bLength;
    unsigned char  bDescriptorType;
    unsigned char  bEndpointAddress;
    unsigned char  bmAttributes;
    unsigned short wMaxPacketSize;
    unsigned char  bInterval;
} usb_audioControlInterruptEndpointDescriptor_t;

// Table 4-26: Standard Audio Streaming (AS) Interface Descriptor
typedef struct _usb_audioStreamingStandardInterfaceDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bInterfaceNumber;
    unsigned char bAlternateSetting;
    unsigned char bNumEndpoints;
    unsigned char bInterfaceClass;
    unsigned char bInterfaceSubClass;
    unsigned char bInterfaceProtocol;
    unsigned char iInterface;
} usb_audioStreamingStandardInterfaceDescriptor_t;

// Table 4-27: Class-Specific Audio Streaming (AS) Interface Descriptor
typedef struct _usb_audioStreamingClassInterfaceDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bTerminalLink;
    unsigned char bmControls;
    unsigned char bFormatType;
    unsigned long bmFormats;
    unsigned char bNrChannels;
    unsigned long bmChannelConfig;
    unsigned char iChannelNames;
} usb_audioStreamingClassInterfaceDescriptor_t;

// Table 4-28: Encoder Descriptor
typedef struct _usb_audioEncoderDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bEncoderID;
    unsigned char bEncoder;
    unsigned long bmControls;
    unsigned char iParam1;
    unsigned char iParam2;
    unsigned char iParam3;
    unsigned char iParam4;
    unsigned char iParam5;
    unsigned char iParam6;
    unsigned char iParam7;
    unsigned char iParam8;
    unsigned char iEncoder;
} usb_audioEncoderDescriptor_t;

// Table 4-29: MPEG Decoder Descriptor
typedef struct _usb_audioMPEGDecoderDescriptor_t
{
    unsigned char  bLength;
    unsigned char  bDescriptorType;
    unsigned char  bDescriptorSubtype;
    unsigned char  bDecoderID;
    unsigned char  bDecoder;
    unsigned short bmMPEGCapabilities;
    unsigned char  bmMPEGFeatures;
    unsigned char  bmControls;
    unsigned char  iDecoder;
} usb_audioMPEGDecoderDescriptor_t;

// Table 4-30: AC-3 Decoder Descriptor
typedef struct _usb_audioAC3DecoderDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bDecoderID;
    unsigned char bDecoder;
    unsigned long bmBSID;
    unsigned char bmAC3Features;
    unsigned char bmControls;
    unsigned char iDecoder;
} usb_audioAC3DecoderDescriptor_t;

// Table 4-31: WMA Decoder Descriptor
typedef struct _usb_audioWMADecoderDescriptor_t
{
    unsigned char  bLength;
    unsigned char  bDescriptorType;
    unsigned char  bDescriptorSubtype;
    unsigned char  bDecoderID;
    unsigned char  bDecoder;
    unsigned short bmWMAProfile;
    unsigned char  bmControls;
    unsigned char  iDecoder;
} usb_audioWMADecoderDescriptor_t;

// Table 4-32: DTS Decoder Descriptor
typedef struct _usb_audioDTSDecoderDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bDecoderID;
    unsigned char bDecoder;
    unsigned char bmCapabilities;
    unsigned char bmControls;
    unsigned char iDecoder;
} usb_audioDTSDecoderDescriptor_t;

// Table 4-33: Standard Audio Streaming (AS) Isochronous Audio Data Endpoint Descriptor
typedef struct _usb_audioStreamingDataStandardEndpointDescriptor_t
{
    unsigned char  bLength;
    unsigned char  bDescriptorType;
    unsigned char  bEndpointAddress;
    unsigned char  bmAttributes;
    unsigned short wMaxPacketSize;
    unsigned char  bInterval;
} usb_audioStreamingDataStandardEndpointDescriptor_t;

// Table 4-34: Class-Specific Audio Streaming (AS) Isochronous Audio Data Endpoint Descriptor
typedef struct _usb_audioStreamingDataClassEndpointDescriptor_t
{
    unsigned char  bLength;
    unsigned char  bDescriptorType;
    unsigned char  bDescriptorSubtype;
    unsigned char  bmAttributes;
    unsigned char  bmControls;
    unsigned char  bLockDelayUnits;
    unsigned short wLockDelay;
} usb_audioStreamingDataClassEndpointDescriptor_t;

// Table 4-35: Standard Audio Streaming (AS) Isochronous Feedback Endpoint Descriptor
typedef struct _usb_audioStreamingFeedbackStandardEndpointDescriptor_t
{
    unsigned char  bLength;
    unsigned char  bDescriptorType;
    unsigned char  bEndpointAddress;
    unsigned char  bmAttributes;
    unsigned short wMaxPacketSize;
    unsigned char  bInterval;
} usb_audioStreamingFeedbackStandardEndpointDescriptor_t;

// *************************************************************************************************
//
// Definitions taken from USB Device Class Definition for Audio Data Formats V2.0
//
// *************************************************************************************************

// Table A-1: Format Type Codes
//		Format Type													Value
#define USB_AUDIO_FORMAT_TYPE_UNDEFINED 0x00 // FORMAT_TYPE_UNDEFINED
#define USB_AUDIO_FORMAT_TYPE_I			0x01 // FORMAT_TYPE_I
#define USB_AUDIO_FORMAT_TYPE_II		0x02 // FORMAT_TYPE_II
#define USB_AUDIO_FORMAT_TYPE_III		0x03 // FORMAT_TYPE_III
#define USB_AUDIO_FORMAT_TYPE_IV		0x04 // FORMAT_TYPE_IV
#define USB_AUDIO_FORMAT_TYPE_EXT_I		0x81 // EXT_FORMAT_TYPE_I
#define USB_AUDIO_FORMAT_TYPE_EXT_II	0x82 // EXT_FORMAT_TYPE_II
#define USB_AUDIO_FORMAT_TYPE_EXT_III	0x83 // EXT_FORMAT_TYPE_III

// Table A-2: Audio Data Format Type I Bit Allocations
// For use with the bmFormats element of usb_audioStreamingClassInterfaceDescriptor_t
//		Format														bmFormats
#define USB_AUDIO_BMFORMATS_TYPE_I_PCM		  (1 << 0)  // PCM
#define USB_AUDIO_BMFORMATS_TYPE_I_PCM8		  (1 << 1)  // PCM8
#define USB_AUDIO_BMFORMATS_TYPE_I_IEEE_FLOAT (1 << 2)  // IEEE_FLOAT
#define USB_AUDIO_BMFORMATS_TYPE_I_ALAW		  (1 << 3)  // ALAW
#define USB_AUDIO_BMFORMATS_TYPE_I_MULAW	  (1 << 4)  // MULAW
#define USB_AUDIO_BMFORMATS_TYPE_I_RAW_DATA	  (1 << 31) // TYPE_I_RAW_DATA

// Table A-3: Audio Data Format Type II Bit Allocations
// For use with the bmFormats element of usb_audioStreamingClassInterfaceDescriptor_t
//		Format														bmFormats
#define USB_AUDIO_BMFORMATS_TYPE_II_MPEG	 (1 << 0)  // MPEG
#define USB_AUDIO_BMFORMATS_TYPE_II_AC_3	 (1 << 1)  // AC-3
#define USB_AUDIO_BMFORMATS_TYPE_II_WMA		 (1 << 2)  // WMA
#define USB_AUDIO_BMFORMATS_TYPE_II_DTS		 (1 << 3)  // DTS
#define USB_AUDIO_BMFORMATS_TYPE_II_RAW_DATA (1 << 31) // TYPE_II_RAW_DATA

// Table A-4: Audio Data Format Type III Bit Allocations
// For use with the bmFormats element of usb_audioStreamingClassInterfaceDescriptor_t
//		Format														bmFormats
#define USB_AUDIO_BMFORMATS_TYPE_III_IEC61937_AC_3				 (1 << 0)  // IEC61937_AC-3
#define USB_AUDIO_BMFORMATS_TYPE_III_IEC61937_MPEG_1_LAYER1		 (1 << 1)  // IEC61937_MPEG-1_Layer1
#define USB_AUDIO_BMFORMATS_TYPE_III_IEC61937_MPEG_1_LAYER2_3	 (1 << 2)  // IEC61937_MPEG-1_Layer2/3 or
                                                                           // IEC61937_MPEG-2_NOEXT
#define USB_AUDIO_BMFORMATS_TYPE_III_IEC61937_MPEG_2_EXT		 (1 << 3)  // IEC61937_MPEG-2_EXT
#define USB_AUDIO_BMFORMATS_TYPE_III_IEC61937_MPEG_2_AAC_ADTS	 (1 << 4)  // IEC61937_MPEG-2_AAC_ADTS
#define USB_AUDIO_BMFORMATS_TYPE_III_IEC61937_MPEG_2_LAYER1_LS	 (1 << 5)  // IEC61937_MPEG-2_Layer1_LS
#define USB_AUDIO_BMFORMATS_TYPE_III_IEC61937_MPEG_2_LAYER2_3_LS (1 << 6)  // IEC61937_MPEG-2_Layer2/3_LS
#define USB_AUDIO_BMFORMATS_TYPE_III_IEC61937_DTS_I				 (1 << 7)  // IEC61937_DTS-I
#define USB_AUDIO_BMFORMATS_TYPE_III_IEC61937_DTS_II			 (1 << 8)  // IEC61937_DTS-II
#define USB_AUDIO_BMFORMATS_TYPE_III_IEC61937_DTS_III			 (1 << 9)  // IEC61937_DTS-III
#define USB_AUDIO_BMFORMATS_TYPE_III_IEC61937_ATRAC				 (1 << 10) // IEC61937_ATRAC
#define USB_AUDIO_BMFORMATS_TYPE_III_IEC61937_ATRAC_2_3			 (1 << 11) // IEC61937_ATRAC_2_3
#define USB_AUDIO_BMFORMATS_TYPE_III_WMA						 (1 << 12) // TYPE_III_WMA

// Table A-5: Audio Data Format Type IV Bit Allocations
// For use with the bmFormats element of usb_audioStreamingClassInterfaceDescriptor_t
//		Format														bmFormats
#define USB_AUDIO_BMFORMATS_TYPE_IV_PCM							(1 << 0)  // PCM
#define USB_AUDIO_BMFORMATS_TYPE_IV_PCM8						(1 << 1)  // PCM8
#define USB_AUDIO_BMFORMATS_TYPE_IV_IEEE_FLOAT					(1 << 2)  // IEEE_FLOAT
#define USB_AUDIO_BMFORMATS_TYPE_IV_ALAW						(1 << 3)  // ALAW
#define USB_AUDIO_BMFORMATS_TYPE_IV_MULAW						(1 << 4)  // MULAW
#define USB_AUDIO_BMFORMATS_TYPE_IV_MPEG						(1 << 5)  // MPEG
#define USB_AUDIO_BMFORMATS_TYPE_IV_AC_3						(1 << 6)  // AC-3
#define USB_AUDIO_BMFORMATS_TYPE_IV_WMA							(1 << 7)  // WMA
#define USB_AUDIO_BMFORMATS_TYPE_IV_IEC61937_AC_3				(1 << 8)  // IEC61937_AC-3
#define USB_AUDIO_BMFORMATS_TYPE_IV_IEC61937_MPEG_1_LAYER1		(1 << 9)  // IEC61937_MPEG-1_Layer1
#define USB_AUDIO_BMFORMATS_TYPE_IV_IEC61937_MPEG_1_LAYER2_3	(1 << 10) // IEC61937_MPEG-1_Layer2/3 or
                                                                          // IEC61937_MPEG-2_NOEXT
#define USB_AUDIO_BMFORMATS_TYPE_IV_IEC61937_MPEG_2_EXT			(1 << 11) // IEC61937_MPEG-2_EXT
#define USB_AUDIO_BMFORMATS_TYPE_IV_IEC61937_MPEG_2_AAC_ADTS	(1 << 12) // IEC61937_MPEG-2_AAC_ADTS
#define USB_AUDIO_BMFORMATS_TYPE_IV_IEC61937_MPEG_2_LAYER1_LS	(1 << 13) // IEC61937_MPEG-2_Layer1_LS
#define USB_AUDIO_BMFORMATS_TYPE_IV_IEC61937_MPEG_2_LAYER2_3_LS (1 << 14) // IEC61937_MPEG-2_Layer2/3_LS
#define USB_AUDIO_BMFORMATS_TYPE_IV_IEC61937_DTS_I				(1 << 15) // IEC61937_DTS-I
#define USB_AUDIO_BMFORMATS_TYPE_IV_IEC61937_DTS_II				(1 << 16) // IEC61937_DTS-II
#define USB_AUDIO_BMFORMATS_TYPE_IV_IEC61937_DTS_III			(1 << 17) // IEC61937_DTS-III
#define USB_AUDIO_BMFORMATS_TYPE_IV_IEC61937_ATRAC				(1 << 18) // IEC61937_ATRAC
#define USB_AUDIO_BMFORMATS_TYPE_IV_IEC61937_ATRAC_2_3			(1 << 19) // IEC61937_ATRAC_2_3
#define USB_AUDIO_BMFORMATS_TYPE_IV_TYPE_III_WMA				(1 << 20) // TYPE_III_WMA
#define USB_AUDIO_BMFORMATS_TYPE_IV_IEC60958_PCM				(1 << 21) // IEC60958_PCM

// Table A-6: Side Band Protocol Codes
//		Side Band Protocol											Value
#define USB_AUDIO_SIDE_BAND_PROTOCOL_UNDEFINED					0x00 // PROTOCOL_UNDEFINED
#define USB_AUDIO_SIDE_BAND_PROTOCOL_PRES_TIMESTAMP				0x01 // PRES_TIMESTAMP_PROTOCOL

// Table 2-2: Type I Format Type Descriptor
typedef struct _usb_audioFormatTypeIDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bFormatType;
    unsigned char bSubslotSize;
    unsigned char bBitResolution;
} usb_audioFormatTypeIDescriptor_t;

// Table 2-3: Type II Format Type Descriptor
typedef struct _usb_audioFormatTypeIIDescriptor_t
{
    unsigned char  bLength;
    unsigned char  bDescriptorType;
    unsigned char  bDescriptorSubtype;
    unsigned char  bFormatType;
    unsigned short wMaxBitRate;
    unsigned short wSlotsPerFrame;
} usb_audioFormatTypeIIDescriptor_t;

// Table 2-4: Type III Format Type Descriptor
typedef struct _usb_audioFormatTypeIIIDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bFormatType;
    unsigned char bSubslotSize;
    unsigned char bBitResolution;
} usb_audioFormatTypeIIIDescriptor_t;

// Table 2-5: Type IV Format Type Descriptor
typedef struct _usb_audioFormatTypeIVDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bFormatType;
} usb_audioFormatTypeIVDescriptor_t;

// Table 2-6: Extended Type I Format Type Descriptor
typedef struct _usb_audioFormatTypeIExtendedDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bFormatType;
    unsigned char bSubslotSize;
    unsigned char bBitResolution;
    unsigned char bHeaderLength;
    unsigned char bControlSize;
    unsigned char bSideBandProtocol;
} usb_audioFormatTypeIExtendedDescriptor_t;

// Table 2-7: Extended Type II Format Type Descriptor
typedef struct _usb_audioFormatTypeIIExtendedDescriptor_t
{
    unsigned char  bLength;
    unsigned char  bDescriptorType;
    unsigned char  bDescriptorSubtype;
    unsigned char  bFormatType;
    unsigned short wMaxBitRate;
    unsigned short wSamplesPerFrame;
    unsigned char  bHeaderLength;
    unsigned char  bSideBandProtocol;
} usb_audioFormatTypeIIExtendedDescriptor_t;

// Table 2-8: Extended Type III Format Type Descriptor
typedef struct _usb_audioFormatTypeIIIExtendedDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bFormatType;
    unsigned char bSubslotSize;
    unsigned char bBitResolution;
    unsigned char bHeaderLength;
    unsigned char bSideBandProtocol;
} usb_audioFormatTypeIIIExtendedDescriptor_t;

// Table 2-9: Hi-Res Presentation TimeStamp Layout
typedef struct _usb_audioHiResPresentationTimeStamp_t
{
    unsigned long bmFlags;
    unsigned long qNanoSecondsHi;
    unsigned long qNanoSecondsLo;
} usb_audioHiResPresentationTimeStamp_t;

// *************************************************************************************************
//
// Definitions taken from Universal Serial Bus Device Class Definition for Terminal Types V2.0
//
// *************************************************************************************************

// Table 2-1: USB Terminal Types
//		Terminal Type												Code
#define USB_AUDIO_TERMINAL_TYPE_USB_UNDEFINED					   0x0100 // USB Undefined
#define USB_AUDIO_TERMINAL_TYPE_USB_STREAMING					   0x0101 // USB streaming
#define USB_AUDIO_TERMINAL_TYPE_USB_VENDOR_SPECIFIC				   0x01FF // USB vendor sepcific

// Table 2-2: Input Terminal Types
//		Input Terminal Type											Code
#define USB_AUDIO_TERMINAL_TYPE_INPUT_UNDEFINED					   0x0200 // Input Undefined
#define USB_AUDIO_TERMINAL_TYPE_INPUT_MICROPHONE				   0x0201 // Microphone
#define USB_AUDIO_TERMINAL_TYPE_INPUT_DESKTOP_MICROPHONE		   0x0202 // Desktop microphone
#define USB_AUDIO_TERMINAL_TYPE_INPUT_PERSONAL_MICROPHONE		   0x0203 // Personal microphone
#define USB_AUDIO_TERMINAL_TYPE_INPUT_OMNIDIRECTIONAL_MICROPHONE   0x0204 // Omni-directional microphone
#define USB_AUDIO_TERMINAL_TYPE_INPUT_MICROPHONE_ARRAY			   0x0205 // Microphone array
#define USB_AUDIO_TERMINAL_TYPE_INPUT_PROCESSING_MICROPHONE_ARRAY  0x0206 // Processing microphone array

// Table 2-3: Output Terminal Types
//		Output Terminal Type										Code
#define USB_AUDIO_TERMINAL_TYPE_OUTPUT_UNDEFINED				   0x0300 // Output Undefined
#define USB_AUDIO_TERMINAL_TYPE_OUTPUT_SPEAKER					   0x0301 // Speaker
#define USB_AUDIO_TERMINAL_TYPE_OUTPUT_HEADPHONES				   0x0302 // Headphones
#define USB_AUDIO_TERMINAL_TYPE_OUTPUT_HEAD_MOUNTED_DISPLAY_AUDIO  0x0303 // Head Mounted Display Audio
#define USB_AUDIO_TERMINAL_TYPE_OUTPUT_DESKTOP_SPEAKER			   0x0304 // Desktop speaker
#define USB_AUDIO_TERMINAL_TYPE_OUTPUT_ROOM_SPEAKER				   0x0305 // Room speaker
#define USB_AUDIO_TERMINAL_TYPE_OUTPUT_COMMUNICATION_SPEAKER	   0x0306 // Communication speaker
#define USB_AUDIO_TERMINAL_TYPE_OUTPUT_LOW_FREQ_EFFECTS_SPEAKER	   0x0307 // Low frequency effects speaker

// Table 2-4: Bi-directional Terminal Types
//		Bi-directional Terminal Type								Code
#define USB_AUDIO_TERMINAL_TYPE_BIDI_UNDEFINED					   0x0400 // Bi-directional Undefined
#define USB_AUDIO_TERMINAL_TYPE_BIDI_HANDSET					   0x0401 // Handset
#define USB_AUDIO_TERMINAL_TYPE_BIDI_HEADSET					   0x0402 // Headset
#define USB_AUDIO_TERMINAL_TYPE_BIDI_SPEAKERPHONE				   0x0403 // Speakerphone, no echo reduction
#define USB_AUDIO_TERMINAL_TYPE_BIDI_ECHO_SUPPRESSING_SPEAKERPHONE 0x0404 // Echo-suppressing speakerphone
#define USB_AUDIO_TERMINAL_TYPE_BIDI_ECHO_CANCELING_SPEAKERPHONE   0x0405 // Echo-canceling speakerphone

// Table 2-5: Telephony Terminal Types
//		Telephony Terminal Type										Code
#define USB_AUDIO_TERMINAL_TYPE_TELEPHONY_UNDEFINED				   0x0500 // Telephony Undefined
#define USB_AUDIO_TERMINAL_TYPE_TELEPHONY_PHONE_LINE			   0x0501 // Phone line
#define USB_AUDIO_TERMINAL_TYPE_TELEPHONY_TELEPHONE				   0x0502 // Telephone
#define USB_AUDIO_TERMINAL_TYPE_TELEPHONY_DOWN_LINE_PHONE		   0x0503 // Down-line Phone

// Table 2-6: External Terminal Types
//		External Terminal Type										Code
#define USB_AUDIO_TERMINAL_TYPE_EXTERNAL_UNDEFINED				   0x0600 // External Undefined
#define USB_AUDIO_TERMINAL_TYPE_EXTERNAL_ANALOG_CONNECTOR		   0x0601 // Analog connector
#define USB_AUDIO_TERMINAL_TYPE_EXTERNAL_DIGITAL_AUDIO_INTERFACE   0x0602 // Digital audio interface
#define USB_AUDIO_TERMINAL_TYPE_EXTERNAL_LINE_CONNECTOR			   0x0603 // Line connector
#define USB_AUDIO_TERMINAL_TYPE_EXTERNAL_LEGACY_AUDIO_CONNECTOR	   0x0604 // Legacy audio connector
#define USB_AUDIO_TERMINAL_TYPE_EXTERNAL_S_PDIF_INTERFACE		   0x0605 // S/PDIF interface
#define USB_AUDIO_TERMINAL_TYPE_EXTERNAL_1394_DA_STREAM			   0x0606 // 1394 DA stream
#define USB_AUDIO_TERMINAL_TYPE_EXTERNAL_1394_DV_STREAM_SOUNDTRACK 0x0607 // 1394 DV stream soundtrack
#define USB_AUDIO_TERMINAL_TYPE_EXTERNAL_ADAT_LIGHTPIPE			   0x0608 // ADAT Lightpipe
#define USB_AUDIO_TERMINAL_TYPE_EXTERNAL_TDIF					   0x0609 // TDIF
#define USB_AUDIO_TERMINAL_TYPE_EXTERNAL_MADI					   0x060A // MADI

// Table 2-7: Embedded Terminal Types
//		Embedded Terminal Type										Code
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_UNDEFINED				   0x0700 // Embedded Undefined
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_LEVEL_CAL_NOISE_SOURCE	   0x0701 // Level Calibration Noise Source
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_EQUALIZATION_NOISE		   0x0702 // Equalization Noise
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_CD_PLAYER				   0x0703 // CD player
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_DAT					   0x0704 // DAT
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_DCC					   0x0705 // DCC
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_COMPRESSED_AUDIO_PLAYER   0x0706 // Compressed Audio Player
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_ANALOG_TAPE			   0x0707 // Analog Tape
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_PHONOGRAPH				   0x0708 // Phonograph
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_VCR_AUDIO				   0x0709 // VCR Audio
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_VIDEO_DISC_AUDIO		   0x070A // Video Disc Audio
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_DVD_AUDIO				   0x070B // DVD Audio
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_TV_TUNER_AUDIO			   0x070C // TV Tuner Audio
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_SATELLITE_RECEIVER_AUDIO  0x070D // Satellite Receiver Audio
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_CABLE_TUNER_AUDIO		   0x070E // Cable Tuner Audio
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_DSS_AUDIO				   0x070F // DSS Audio
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_RADIO_RECEIVER			   0x0710 // Radio Receiver
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_RADIO_TRANSMITTER		   0x0711 // Radio Transmitter
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_MULTI_TRACK_RECORDER	   0x0712 // Multi-track Recorder
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_SYNTHESIZER			   0x0713 // Synthesizer
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_PIANO					   0x0714 // Piano
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_GUITAR					   0x0715 // Guitar
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_DRUMS_RHYTHM			   0x0716 // Drums/Rhythm
#define USB_AUDIO_TERMINAL_TYPE_EMBEDDED_OTHER_MUSICAL_INSTRUMENT  0x0717 // Other Musical Instrument

// *************************************************************************************************
//
// Definitions taken from Universal Serial Bus Device Class Definition for MIDI Devices V1.0
//
// *************************************************************************************************

// Table A-1: MIDIStreaming (MS) Class-Specific Interface Descriptor Subtypes
//		Descriptor Subtypes											Value
#define USB_DESCRIPTOR_SUBTYPE_MIDI_UNDEFINED  0x00 // MS_DESCRIPTOR_UNDEFINED
#define USB_DESCRIPTOR_SUBTYPE_MIDI_HEADER	   0x01 // MS_HEADER
#define USB_DESCRIPTOR_SUBTYPE_MIDI_IN_JACK	   0x02 // MIDI_IN_JACK
#define USB_DESCRIPTOR_SUBTYPE_MIDI_OUT_JACK   0x03 // MIDI_OUT_JACK
#define USB_DESCRIPTOR_SUBTYPE_MIDI_ELEMENT	   0x04 // ELEMENT

// Table A-2: MIDIStreaming (MS) Class-Specific Endpoint Descriptor Subtypes
//		MIDI Endpoint Subtype										Value
#define USB_ENDPOINT_DESCRIPTOR_MIDI_UNDEFINED 0x00 // DESCRIPTOR_UNDEFINED
#define USB_ENDPOINT_DESCRIPTOR_MIDI_GENERAL   0x01 // MS_GENERAL

// Table A-3: MIDIStreaming (MS) MIDI IN and OUT Jack types
//		Jack Type													Value
#define USB_MIDI_JACK_TYPE_UNDEFINED		   0x00 // JACK_TYPE_UNDEFINED
#define USB_MIDI_JACK_TYPE_EMBEDDED			   0x01 // EMBEDDED
#define USB_MIDI_JACK_TYPE_EXTERNAL			   0x02 // EXTERNAL

// Table A.5.1 Endpoint Control Selectors
//		Endpoint Control Selector									Value
#define USB_MIDI_ENDPOINT_CONTROL_UNDEFINED	   0x00 // EP_CONTROL_UNDEFINED
#define USB_MIDI_ENDPOINT_CONTROL_ASSOCIATION  0x01 // ASSOCIATION_CONTROL

// Table 6-1: Standard MIDIStreaming Interface Descriptor
// Identical to standard USB interface descriptor

// Table 6-2: Class-Specific MIDIStreaming (MS) Interface Header Descriptor
typedef struct _usb_audioMIDIStreamingClassInterfaceDescriptor_t
{
    unsigned char  bLength;
    unsigned char  bDescriptorType;
    unsigned char  bDescriptorSubtype;
    unsigned short bcdMSC;
    unsigned short wTotalLength;
} usb_audioMIDIStreamingClassInterfaceDescriptor_t;

// Table 6-3: MIDI IN Jack Descriptor
typedef struct _usb_audioMIDIInJackDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bJackType;
    unsigned char bJackID;
    unsigned char iJack;
} usb_audioMIDIInJackDescriptor_t;

// Table 6-4: MIDI OUT Jack Descriptor
typedef struct _usb_audioMIDIOutJackDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bJackType;
    unsigned char bJackID;
    unsigned char bNrInputPins;
    unsigned char baSourceID1;
    unsigned char BaSourcePin1;
    //	...
    //	unsigned char baSourceIDp;
    //	unsigned char BaSourcePinp;
    unsigned char iJack;
} usb_audioMIDIOutJackDescriptor_t;

// Table 6-5: MIDI Element Descriptor
typedef struct _usb_audioMIDIElementDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bElementID;
    unsigned char bNrInputPins;
    unsigned char baSourceID1;
    unsigned char BaSourcePin1;
    //	...
    //	unsigned char baSourceIDp;
    //	unsigned char BaSourcePinp;
    unsigned char bNrOutputPins;
    unsigned char bInTerminalLink;
    unsigned char bOutTerminalLink;
    unsigned char bElCapsSize;
    unsigned char bmElementCaps;       // size determined by bElCapsSize
    unsigned char iElement;
} usb_audioMIDIElementDescriptor_t;

// Section 6.1.2.4 - Element Descriptor bmElementCaps bits
//		Element Capability											bmElementCaps
#define USB_MIDI_BMELEMENTCAPS_CUSTOM_UNDEFINED (1 << 0)  // CUSTOM UNDEFINED
#define USB_MIDI_BMELEMENTCAPS_CLOCK			(1 << 1)  // MIDI CLOCK
#define USB_MIDI_BMELEMENTCAPS_TIME_CODE		(1 << 2)  // MIDI TIME CODE
#define USB_MIDI_BMELEMENTCAPS_MACHINE_CONTROL	(1 << 3)  // MIDI MACHINE CONTROL
#define USB_MIDI_BMELEMENTCAPS_GM1				(1 << 4)  // GM1 - General MIDI
#define USB_MIDI_BMELEMENTCAPS_GM2				(1 << 5)  // GM2 - General MIDI
#define USB_MIDI_BMELEMENTCAPS_GS				(1 << 6)  // GS - Roland
#define USB_MIDI_BMELEMENTCAPS_XG				(1 << 7)  // XG - Yamaha
#define USB_MIDI_BMELEMENTCAPS_EFX				(1 << 8)  // EFX
#define USB_MIDI_BMELEMENTCAPS_PATCH_BAY		(1 << 9)  // MIDI Patch Bay
#define USB_MIDI_BMELEMENTCAPS_DLS1				(1 << 10) // DLS1
#define USB_MIDI_BMELEMENTCAPS_DLS2				(1 << 11) // DLS2

// Table 6-6: Standard MIDIStreaming (MS) Bulk Data Endpoint Descriptor
// Identical to standard USB endpoint descriptor

// Table 6-7: Class-specific MIDIStreaming (MS) Bulk Data Endpoint Descriptor
typedef struct _usb_audioMIDIStreamingClassBulkDataEndpointDescriptor_t
{
    unsigned char bLength;
    unsigned char bDescriptorType;
    unsigned char bDescriptorSubtype;
    unsigned char bNumEmbMIDIJack;
    unsigned char baAssocJackID1;
    //	...
    //	unsigned char baAssocJackIDn;
} usb_audioMIDIStreamingClassBulkDataEndpointDescriptor_t;

// Table 6-8: Standard MIDIStreaming (MS) Transfer Bulk Data Endpoint Descriptor
// Identical to standard USB endpoint descriptor

#endif                                 /* __USBAUDIO_H__ */
