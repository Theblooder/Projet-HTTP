#ifndef __CONSTRUCTANSWER_H__
#define __CONSTRUCTANSWER_H__

/*Prototype*/

typedef struct answer {
    int clientID;
    int lenSL; 
    char *bufSL;
    struct header *headers;
    int lenMB;
    char *bufMB;
    int isMBallocate;
} Answer;

typedef struct header {
    int len;
    char *buf;
    struct header *next;
} Header;

/* !! La fonction qui nettoit la réponse doit aussi free tout les buf qui ont été crée car chaque buf va correspondre à une allocation de mémoire */

/**
 * @brief To allocate the answer
 * 
 */
void initAnswer(int clientID);

/**
 * @brief Purge the answer (and all the bufs allocate)
 * 
 */
void purgeAnswer();

/**
 * @brief Just purge the headers
 * 
 */
void purgeHeaders();

/**
 * @brief Construct the answer to send it
 * 
 * @param int l'id du client
 * @return int 0 if everyting is ok, -1 else
 */
int sendAnswerToClient();

/**
 * @brief to define the start line (the function will reallocate the memory needed)
 * 
 * @param httpVersion (3 character like 1.2)
 * @param statusCode 
 * @param reasonPhrase 
 * @return int 0 if good -1 else 
 */
int constructFirstLine(char *httpVersion, int statusCode, char *reasonPhrase);

/**
 * @brief to define the messqge body (you can choose if you want to allocate memory)
 * 
 * @param message 
 * @param len 
 * @param needToAllocate 
 * @return int 
 */
int constructMessageBody(char *message, int len, int needToAllocate);

/**
 * @brief to construct/add one header to the answer
 * 
 * @param header 
 * @param len 
 * @return int 
 */
int constructHeader(char *header, int len);

#endif