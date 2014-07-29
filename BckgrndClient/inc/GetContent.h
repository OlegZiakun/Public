/*
 * GetContent.h
 *
 * Author: Oleg Ziakun
 */

#ifndef GETCONTENT_H_
#define GETCONTENT_H_

#include "HTTPEngine.h"

class MGetContentObserver
	{
public:
	
	virtual void GetNextContent(const TDesC& aURL, const TDesC& aSavedFileName) = 0;	
	
	};

class CGetContent : public CBase, public MHTTPObserver
	{
public:

	static CGetContent* NewL(MGetContentObserver& aObserver);

	~CGetContent();
	
    void Download(const TDesC& aURL, const TDesC& aSavedFileName);

private:
	
	CGetContent(MGetContentObserver& aObserver);
	
	void ConstructL();
	
private:

	virtual void OnHTTPEvent(const TDesC & aEventDescription);

private:

	MGetContentObserver& iObserver;
	CHTTPEngine * iEngine;
	TBuf<KDefaultBufferSize> iURI;
	TBuf8<KDefaultBufferSize> iURI8;
	
	};

#endif /* GETCONTENT_H_ */
