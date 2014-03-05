#ifndef _OUTGAUGE_H_
#define _OUTGAUGE_H_

// OutGauge - EXTERNAL DASHBOARD SUPPORT
// ========

// The user's car in multiplayer or the viewed car in single player or
// single player replay can output information to a dashboard system
// while viewed from an internal view.

// This can be controlled by 5 lines in the cfg.txt file :

// OutGauge Mode 0        :0-off 1-driving 2-driving+replay
// OutGauge Delay 1       :minimum delay between packets (100ths of a sec)
// OutGauge IP 0.0.0.0    :IP address to send the UDP packet
// OutGauge Port 0        :IP port
// OutGauge ID 0          :if not zero, adds an identifier to the packet

typedef unsigned char byte;
typedef unsigned short word;

// Each update sends the following UDP packet :

struct OutGaugePack
{
	unsigned int Time;			// time in milliseconds (to check order)

	char		Car[4];			// Car name
	word		Flags;			// Info (see OG_x below)
	byte		Gear;			// Reverse:0, Neutral:1, First:2...
	byte		PLID;			// Unique ID of viewed player (0 = none)
	float		Speed;			// M/S
	float		RPM;			// RPM
	float		Turbo;			// BAR
	float		EngTemp;		// C
	float		Fuel;			// 0 to 1
	float		OilPressure;	// BAR
	float		OilTemp;		// C
	unsigned	DashLights;		// Dash lights available (see DL_x below)
	unsigned	ShowLights;		// Dash lights currently switched on
	float		Throttle;		// 0 to 1
	float		Brake;			// 0 to 1
	float		Clutch;			// 0 to 1
	char		Display1[16];	// Usually Fuel
	char		Display2[16];	// Usually Settings

	int			ID;				// optional - only if OutGauge ID is specified
};

// OG_x - bits for OutGaugePack Flags

#define OG_SHIFT		1		// key
#define OG_CTRL			2		// key

#define OG_TURBO		8192	// show turbo gauge
#define OG_KM			16384	// if not set - user prefers MILES
#define OG_BAR			32768	// if not set - user prefers PSI

// DL_x - bits for OutGaugePack DashLights and ShowLights

enum
{
	DL_SHIFT,			// bit 0	- shift light
	DL_FULLBEAM,		// bit 1	- full beam
	DL_HANDBRAKE,		// bit 2	- handbrake
	DL_PITSPEED,		// bit 3	- pit speed limiter
	DL_TC,				// bit 4	- TC active or switched off
	DL_SIGNAL_L,		// bit 5	- left turn signal
	DL_SIGNAL_R,		// bit 6	- right turn signal
	DL_SIGNAL_ANY,		// bit 7	- shared turn signal
	DL_OILWARN,			// bit 8	- oil pressure warning
	DL_BATTERY,			// bit 9	- battery warning
	DL_ABS,				// bit 10	- ABS active or switched off
	DL_SPARE,			// bit 11
	DL_NUM
};

//////
#endif