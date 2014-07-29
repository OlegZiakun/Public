#ifndef DEFS_H
#define DEFS_H

_LIT(KHttpPrefix, "http://");
_LIT8(KHttpPrefix8, "http://");
_LIT(KHttpsPrefix, "https://");
_LIT8(KHttpsPrefix8, "https://");
_LIT8(KMimeType, "text/plain");
_LIT(KSucceeded,"ESucceeded");
_LIT(KDefaultDelay,"4");

_LIT(KTxtFile,"http://www.linkedin.com/");
_LIT(KImgFile,"http://www.themusicvoid.com/wp-content/uploads/2011/02/researching-careers-music81.jpg");   
_LIT(KTxtSavedFile,"C:\\private\\E7ADC8DC\\linkedin.htm");
_LIT(KImgSavedFile,"C:\\private\\E7ADC8DC\\image.jpg");
_LIT(KIniFile,"C:\\private\\E7ADC8DC\\options.ini");

#define OFFLINE 5

// Used user agent for requests
_LIT8(KUserAgent, "BackgroundClient");
// This client accepts all content types.
_LIT8(KAccept, "*/*");

const TInt KStatustextBufferSize = 128;
const TInt KInfotextBufferSize = 128;
const TInt KURIBufferSize = 256;

#endif // DEFS_H
