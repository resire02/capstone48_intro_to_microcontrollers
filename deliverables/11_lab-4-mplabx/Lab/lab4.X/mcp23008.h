
#ifndef MCP23008_H
#define	MCP23008_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MCP_LED_CHUNK_SIZE 512UL

void mcp_leds_init();
void mcp_write_leds(uint8_t val);

#ifdef	__cplusplus
}
#endif

#endif	/* MCP23008_H */

