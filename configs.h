#ifndef CONFIGS_H_
#define CONFIGS_H_

#define SQLI_WORDS	"select", "union", "and 1=1", "or 1=1", "sleep"
#define SQLI_LIMIT 15
#define XSS_WORDS "alert", "onerror", "onload", "confirm", "src="
#define XSS_LIMIT 15
#define DOS_INTERVAL 1000
#define DOS_LIMIT	100

#endif /* CONFIGS_H_ */
