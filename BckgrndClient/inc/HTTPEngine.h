/*
 * GetContent.cpp
 *
 * Author: Oleg Ziakun
 */

#ifndef __HTTPENGINE_H__
#define __HTTPENGINE_H__
#include <coecntrl.h>
#include <http\rhttpsession.h>
#include <http\mhttpdatasupplier.h>
#include <http\mhttptransactioncallback.h>
#include <http\mhttpauthenticationcallback.h>
#include <http\RHTTPTransaction.h>
#include <http\RHTTPHeaders.h>
#include <es_sock.h>
#include <apsettingshandlerui.h>
#include <centralrepository.h>
#include <ProfileEngineSDKCRKeys.h>
#include <activeapdb.h>
#include <Defs.h>

const TInt KDefaultBufferSize = 256;

class MHTTPObserver
	{
public:
	
	virtual void OnHTTPEvent(const TDesC& aEventDescription) = 0;
	};

class CHTTPEngine : public CBase,
		public MHTTPTransactionCallback,
		public MHTTPDataSupplier,
		public MHTTPAuthenticationCallback
	{
public:

	static CHTTPEngine* NewL(MHTTPObserver & aObserver);

	~CHTTPEngine();

	void IssueHTTPGetL(const TDesC8& aUri, const TDesC& aFileName);

	void CancelTransaction();

	inline TBool IsRunning()
		{
		return iRunning;
		}

private:

	//! constructor
	CHTTPEngine(MHTTPObserver & aObserver);

	void SetHeaderL(RHTTPHeaders aHeaders, TInt aHdrField,
			const TDesC8& aHdrValue);

	void SetupConnectionL();

	void RespHeader(RHTTPTransaction& aTransaction);

	void RespBodyData(RHTTPTransaction& aTransaction);

	/*!
	 * From MHTTPSessionEventCallback
	 */
private:

	void MHFRunL(RHTTPTransaction aTransaction, const THTTPEvent& aEvent);

	/*!
	 * MHFRunError()
	 *
	 *Called by framework when *leave* occurs in handling of transaction event.
	 *
	 * 
	 *   aError:     The leave code that occured.
	 *   aTransaction: The transaction that was being processed when leave
	 *           occured.
	 *   aEvent:     The event that was being processed when leave
	 *           occured.
	 *
	 * 
	 *    KErrNone, if the error was handled. Otherwise the value of aError, or
	 *   some other error value. Returning error value causes causes
	 *   HTTP-CORE 6 panic.
	 *
	 */
	TInt MHFRunError(TInt aError, RHTTPTransaction aTransaction,
			const THTTPEvent& aEvent);

	/*!
	 * From MHTTPDataSupplier (needed for HTTP POST)
	 */
private:
	
	/*!
	 * ReleaseData()
	 *
	 * Called by framework to allow data supplier to release resources
	 * related to previous data part.
	 *
	 */
	void ReleaseData();

	/*!
	 * GetNextDataPart()
	 *
	 * Called when next data part is needed.
	 *
	 *
	 *   aDataPart: Must be set to point to the next data part.
	 *
	 *
	 *     ETrue if the provided data part is the last one. If more data parts
	 *   are needed after the provided one, return EFalse.
	 *
	 */
	TBool GetNextDataPart(TPtrC8& aDataPart);

	/*!
	 * Reset()
	 *
	 *  Called by framework to reset the data supplier to its initial state.
	 *
	 *
	 *   KErrNone if successfull.
	 *
	 */
	TInt Reset();

	/*!
	 * OverallDataSize()
	 *
	 * Called by framework when it needs to know the size of the
	 * body data.
	 * 
	 *     Size of the data, or KErrNotFound (or KErrNotSupported)
	 *   if the size of the data is not known.
	 *
	 */
	TInt OverallDataSize();

	/*!
	 * From MHTTPAuthenticationCallback (needed for HTTP authentication)
	 */
private:
	
	/*!
	 * GetCredentialsL()
	 *
	 *  Called by framework when username and password for requested URI is
	 * needed.
	 *
	 * 
	 *   aURI: The URI being requested (e.g. "http://host.org")
	 *   aRealm: The realm being requested (e.g. "user@host.org")
	 *   aAuthenticationType: Authentication type. (e.g. "Basic")
	 *   aUsername: Given user name.
	 *   aPassword: Given password.
	 *
	 *
	 *     A pointer to the created document
	 *
	 */
	TBool GetCredentialsL(const TUriC8& aURI, RString aRealm,
			RStringF aAuthenticationType, RString& aUsername,
			RString& aPassword);

	/**
	 * Returns ETrue if an existing connection can be found; EFalse, if not
	 */
	TBool FindExistingConnection(void);

private:

	RHTTPSession iSession;
	RHTTPTransaction iTransaction;
	MHTTPObserver & iObserver;
	HBufC8* iPostData;
	TBool iRunning;
	TBool iConnectionSetupDone;
	RFile iFile;
	RFs iFs;
	TBuf<KDefaultBufferSize> iCurrentFileName;
	HBufC* iResponseBuffer;
	TInt iFullSize;
	CRepository* iRepository;
	TInt iPrevProfileId;
	RSocketServ iSocketServ;
	RConnection iConnection;
	TUint32 iSelectedIap;
	
	};

#endif // __HTTPENGINE_H__
