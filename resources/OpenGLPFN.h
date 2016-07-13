#if !defined(PFNGLGETSTRINGPROC)
typedef const GLubyte*(*PFNGLGETSTRINGPROC)(GLenum);
#endif
#if !defined(PFNGLGETSTRINGIPROC)
typedef const GLubyte*(*PFNGLGETSTRINGIPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLQUERYMATRIXXOESPROC)
typedef GLbitfield(*PFNGLQUERYMATRIXXOESPROC)(GLfixed*,GLint*);
#endif
#if !defined(PFNGLAREPROGRAMSRESIDENTNVPROC)
typedef GLboolean(*PFNGLAREPROGRAMSRESIDENTNVPROC)(GLsizei,const GLuint*,GLboolean*);
#endif
#if !defined(PFNGLARETEXTURESRESIDENTEXTPROC)
typedef GLboolean(*PFNGLARETEXTURESRESIDENTEXTPROC)(GLsizei,const GLuint*,GLboolean*);
#endif
#if !defined(PFNGLARETEXTURESRESIDENTPROC)
typedef GLboolean(*PFNGLARETEXTURESRESIDENTPROC)(GLsizei,const GLuint*,GLboolean*);
#endif
#if !defined(PFNGLISASYNCMARKERSGIXPROC)
typedef GLboolean(*PFNGLISASYNCMARKERSGIXPROC)(GLuint);
#endif
#if !defined(PFNGLISBUFFERARBPROC)
typedef GLboolean(*PFNGLISBUFFERARBPROC)(GLuint);
#endif
#if !defined(PFNGLISBUFFERPROC)
typedef GLboolean(*PFNGLISBUFFERPROC)(GLuint);
#endif
#if !defined(PFNGLISBUFFERRESIDENTNVPROC)
typedef GLboolean(*PFNGLISBUFFERRESIDENTNVPROC)(GLenum);
#endif
#if !defined(PFNGLISCOMMANDLISTNVPROC)
typedef GLboolean(*PFNGLISCOMMANDLISTNVPROC)(GLuint);
#endif
#if !defined(PFNGLISENABLEDPROC)
typedef GLboolean(*PFNGLISENABLEDPROC)(GLenum);
#endif
#if !defined(PFNGLISENABLEDIPROC)
typedef GLboolean(*PFNGLISENABLEDIPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLISENABLEDINDEXEDEXTPROC)
typedef GLboolean(*PFNGLISENABLEDINDEXEDEXTPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLISFENCEAPPLEPROC)
typedef GLboolean(*PFNGLISFENCEAPPLEPROC)(GLuint);
#endif
#if !defined(PFNGLISFENCENVPROC)
typedef GLboolean(*PFNGLISFENCENVPROC)(GLuint);
#endif
#if !defined(PFNGLISFRAMEBUFFEREXTPROC)
typedef GLboolean(*PFNGLISFRAMEBUFFEREXTPROC)(GLuint);
#endif
#if !defined(PFNGLISFRAMEBUFFERPROC)
typedef GLboolean(*PFNGLISFRAMEBUFFERPROC)(GLuint);
#endif
#if !defined(PFNGLISIMAGEHANDLERESIDENTARBPROC)
typedef GLboolean(*PFNGLISIMAGEHANDLERESIDENTARBPROC)(GLuint64);
#endif
#if !defined(PFNGLISIMAGEHANDLERESIDENTNVPROC)
typedef GLboolean(*PFNGLISIMAGEHANDLERESIDENTNVPROC)(GLuint64);
#endif
#if !defined(PFNGLISLISTPROC)
typedef GLboolean(*PFNGLISLISTPROC)(GLuint);
#endif
#if !defined(PFNGLISNAMEAMDPROC)
typedef GLboolean(*PFNGLISNAMEAMDPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLISNAMEDBUFFERRESIDENTNVPROC)
typedef GLboolean(*PFNGLISNAMEDBUFFERRESIDENTNVPROC)(GLuint);
#endif
#if !defined(PFNGLISNAMEDSTRINGARBPROC)
typedef GLboolean(*PFNGLISNAMEDSTRINGARBPROC)(GLint,const GLchar*);
#endif
#if !defined(PFNGLISOBJECTBUFFERATIPROC)
typedef GLboolean(*PFNGLISOBJECTBUFFERATIPROC)(GLuint);
#endif
#if !defined(PFNGLISOCCLUSIONQUERYNVPROC)
typedef GLboolean(*PFNGLISOCCLUSIONQUERYNVPROC)(GLuint);
#endif
#if !defined(PFNGLISPATHNVPROC)
typedef GLboolean(*PFNGLISPATHNVPROC)(GLuint);
#endif
#if !defined(PFNGLISPOINTINFILLPATHNVPROC)
typedef GLboolean(*PFNGLISPOINTINFILLPATHNVPROC)(GLuint,GLuint,GLfloat,GLfloat);
#endif
#if !defined(PFNGLISPOINTINSTROKEPATHNVPROC)
typedef GLboolean(*PFNGLISPOINTINSTROKEPATHNVPROC)(GLuint,GLfloat,GLfloat);
#endif
#if !defined(PFNGLISPROGRAMARBPROC)
typedef GLboolean(*PFNGLISPROGRAMARBPROC)(GLuint);
#endif
#if !defined(PFNGLISPROGRAMPROC)
typedef GLboolean(*PFNGLISPROGRAMPROC)(GLuint);
#endif
#if !defined(PFNGLISPROGRAMNVPROC)
typedef GLboolean(*PFNGLISPROGRAMNVPROC)(GLuint);
#endif
#if !defined(PFNGLISPROGRAMPIPELINEPROC)
typedef GLboolean(*PFNGLISPROGRAMPIPELINEPROC)(GLuint);
#endif
#if !defined(PFNGLISQUERYARBPROC)
typedef GLboolean(*PFNGLISQUERYARBPROC)(GLuint);
#endif
#if !defined(PFNGLISQUERYPROC)
typedef GLboolean(*PFNGLISQUERYPROC)(GLuint);
#endif
#if !defined(PFNGLISRENDERBUFFEREXTPROC)
typedef GLboolean(*PFNGLISRENDERBUFFEREXTPROC)(GLuint);
#endif
#if !defined(PFNGLISRENDERBUFFERPROC)
typedef GLboolean(*PFNGLISRENDERBUFFERPROC)(GLuint);
#endif
#if !defined(PFNGLISSAMPLERPROC)
typedef GLboolean(*PFNGLISSAMPLERPROC)(GLuint);
#endif
#if !defined(PFNGLISSHADERPROC)
typedef GLboolean(*PFNGLISSHADERPROC)(GLuint);
#endif
#if !defined(PFNGLISSTATENVPROC)
typedef GLboolean(*PFNGLISSTATENVPROC)(GLuint);
#endif
#if !defined(PFNGLISSYNCPROC)
typedef GLboolean(*PFNGLISSYNCPROC)(GLsync);
#endif
#if !defined(PFNGLISTEXTUREEXTPROC)
typedef GLboolean(*PFNGLISTEXTUREEXTPROC)(GLuint);
#endif
#if !defined(PFNGLISTEXTUREPROC)
typedef GLboolean(*PFNGLISTEXTUREPROC)(GLuint);
#endif
#if !defined(PFNGLISTEXTUREHANDLERESIDENTARBPROC)
typedef GLboolean(*PFNGLISTEXTUREHANDLERESIDENTARBPROC)(GLuint64);
#endif
#if !defined(PFNGLISTEXTUREHANDLERESIDENTNVPROC)
typedef GLboolean(*PFNGLISTEXTUREHANDLERESIDENTNVPROC)(GLuint64);
#endif
#if !defined(PFNGLISTRANSFORMFEEDBACKPROC)
typedef GLboolean(*PFNGLISTRANSFORMFEEDBACKPROC)(GLuint);
#endif
#if !defined(PFNGLISTRANSFORMFEEDBACKNVPROC)
typedef GLboolean(*PFNGLISTRANSFORMFEEDBACKNVPROC)(GLuint);
#endif
#if !defined(PFNGLISVARIANTENABLEDEXTPROC)
typedef GLboolean(*PFNGLISVARIANTENABLEDEXTPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLISVERTEXARRAYAPPLEPROC)
typedef GLboolean(*PFNGLISVERTEXARRAYAPPLEPROC)(GLuint);
#endif
#if !defined(PFNGLISVERTEXARRAYPROC)
typedef GLboolean(*PFNGLISVERTEXARRAYPROC)(GLuint);
#endif
#if !defined(PFNGLISVERTEXATTRIBENABLEDAPPLEPROC)
typedef GLboolean(*PFNGLISVERTEXATTRIBENABLEDAPPLEPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLPOINTALONGPATHNVPROC)
typedef GLboolean(*PFNGLPOINTALONGPATHNVPROC)(GLuint,GLsizei,GLsizei,GLfloat,GLfloat*,GLfloat*,GLfloat*,GLfloat*);
#endif
#if !defined(PFNGLTESTFENCEAPPLEPROC)
typedef GLboolean(*PFNGLTESTFENCEAPPLEPROC)(GLuint);
#endif
#if !defined(PFNGLTESTFENCENVPROC)
typedef GLboolean(*PFNGLTESTFENCENVPROC)(GLuint);
#endif
#if !defined(PFNGLTESTOBJECTAPPLEPROC)
typedef GLboolean(*PFNGLTESTOBJECTAPPLEPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLUNMAPBUFFERARBPROC)
typedef GLboolean(*PFNGLUNMAPBUFFERARBPROC)(GLenum);
#endif
#if !defined(PFNGLUNMAPBUFFERPROC)
typedef GLboolean(*PFNGLUNMAPBUFFERPROC)(GLenum);
#endif
#if !defined(PFNGLUNMAPNAMEDBUFFEREXTPROC)
typedef GLboolean(*PFNGLUNMAPNAMEDBUFFEREXTPROC)(GLuint);
#endif
#if !defined(PFNGLUNMAPNAMEDBUFFERPROC)
typedef GLboolean(*PFNGLUNMAPNAMEDBUFFERPROC)(GLuint);
#endif
#if !defined(PFNGLVDPAUISSURFACENVPROC)
typedef GLboolean(*PFNGLVDPAUISSURFACENVPROC)(GLvdpauSurfaceNV);
#endif
#if !defined(PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)
typedef GLenum(*PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)(GLenum);
#endif
#if !defined(PFNGLCHECKFRAMEBUFFERSTATUSPROC)
typedef GLenum(*PFNGLCHECKFRAMEBUFFERSTATUSPROC)(GLenum);
#endif
#if !defined(PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC)
typedef GLenum(*PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC)
typedef GLenum(*PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLCLIENTWAITSYNCPROC)
typedef GLenum(*PFNGLCLIENTWAITSYNCPROC)(GLsync,GLbitfield,GLuint64);
#endif
#if !defined(PFNGLGETERRORPROC)
typedef GLenum(*PFNGLGETERRORPROC)();
#endif
#if !defined(PFNGLGETGRAPHICSRESETSTATUSPROC)
typedef GLenum(*PFNGLGETGRAPHICSRESETSTATUSPROC)();
#endif
#if !defined(PFNGLGETGRAPHICSRESETSTATUSARBPROC)
typedef GLenum(*PFNGLGETGRAPHICSRESETSTATUSARBPROC)();
#endif
#if !defined(PFNGLOBJECTPURGEABLEAPPLEPROC)
typedef GLenum(*PFNGLOBJECTPURGEABLEAPPLEPROC)(GLenum,GLuint,GLenum);
#endif
#if !defined(PFNGLOBJECTUNPURGEABLEAPPLEPROC)
typedef GLenum(*PFNGLOBJECTUNPURGEABLEAPPLEPROC)(GLenum,GLuint,GLenum);
#endif
#if !defined(PFNGLPATHGLYPHINDEXARRAYNVPROC)
typedef GLenum(*PFNGLPATHGLYPHINDEXARRAYNVPROC)(GLuint,GLenum,const void*,GLbitfield,GLuint,GLsizei,GLuint,GLfloat);
#endif
#if !defined(PFNGLPATHGLYPHINDEXRANGENVPROC)
typedef GLenum(*PFNGLPATHGLYPHINDEXRANGENVPROC)(GLenum,const void*,GLbitfield,GLuint,GLfloat,GLuint);
#endif
#if !defined(PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC)
typedef GLenum(*PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC)(GLuint,GLenum,GLsizeiptr,const void*,GLsizei,GLuint,GLsizei,GLuint,GLfloat);
#endif
#if !defined(PFNGLVIDEOCAPTURENVPROC)
typedef GLenum(*PFNGLVIDEOCAPTURENVPROC)(GLuint,GLuint*,GLuint64EXT*);
#endif
#if !defined(PFNGLGETPATHLENGTHNVPROC)
typedef GLfloat(*PFNGLGETPATHLENGTHNVPROC)(GLuint,GLsizei,GLsizei);
#endif
#if !defined(PFNGLCREATEPROGRAMOBJECTARBPROC)
typedef GLhandleARB(*PFNGLCREATEPROGRAMOBJECTARBPROC)();
#endif
#if !defined(PFNGLCREATESHADEROBJECTARBPROC)
typedef GLhandleARB(*PFNGLCREATESHADEROBJECTARBPROC)(GLenum);
#endif
#if !defined(PFNGLGETHANDLEARBPROC)
typedef GLhandleARB(*PFNGLGETHANDLEARBPROC)(GLenum);
#endif
#if !defined(PFNGLFINISHASYNCSGIXPROC)
typedef GLint(*PFNGLFINISHASYNCSGIXPROC)(GLuint*);
#endif
#if !defined(PFNGLGETATTRIBLOCATIONARBPROC)
typedef GLint(*PFNGLGETATTRIBLOCATIONARBPROC)(GLhandleARB,const GLcharARB*);
#endif
#if !defined(PFNGLGETATTRIBLOCATIONPROC)
typedef GLint(*PFNGLGETATTRIBLOCATIONPROC)(GLuint,const GLchar*);
#endif
#if !defined(PFNGLGETFRAGDATAINDEXPROC)
typedef GLint(*PFNGLGETFRAGDATAINDEXPROC)(GLuint,const GLchar*);
#endif
#if !defined(PFNGLGETFRAGDATALOCATIONEXTPROC)
typedef GLint(*PFNGLGETFRAGDATALOCATIONEXTPROC)(GLuint,const GLchar*);
#endif
#if !defined(PFNGLGETFRAGDATALOCATIONPROC)
typedef GLint(*PFNGLGETFRAGDATALOCATIONPROC)(GLuint,const GLchar*);
#endif
#if !defined(PFNGLGETINSTRUMENTSSGIXPROC)
typedef GLint(*PFNGLGETINSTRUMENTSSGIXPROC)();
#endif
#if !defined(PFNGLGETPROGRAMRESOURCELOCATIONPROC)
typedef GLint(*PFNGLGETPROGRAMRESOURCELOCATIONPROC)(GLuint,GLenum,const GLchar*);
#endif
#if !defined(PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC)
typedef GLint(*PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC)(GLuint,GLenum,const GLchar*);
#endif
#if !defined(PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)
typedef GLint(*PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)(GLuint,GLenum,const GLchar*);
#endif
#if !defined(PFNGLGETUNIFORMBUFFERSIZEEXTPROC)
typedef GLint(*PFNGLGETUNIFORMBUFFERSIZEEXTPROC)(GLuint,GLint);
#endif
#if !defined(PFNGLGETUNIFORMLOCATIONARBPROC)
typedef GLint(*PFNGLGETUNIFORMLOCATIONARBPROC)(GLhandleARB,const GLcharARB*);
#endif
#if !defined(PFNGLGETUNIFORMLOCATIONPROC)
typedef GLint(*PFNGLGETUNIFORMLOCATIONPROC)(GLuint,const GLchar*);
#endif
#if !defined(PFNGLGETVARYINGLOCATIONNVPROC)
typedef GLint(*PFNGLGETVARYINGLOCATIONNVPROC)(GLuint,const GLchar*);
#endif
#if !defined(PFNGLPOLLASYNCSGIXPROC)
typedef GLint(*PFNGLPOLLASYNCSGIXPROC)(GLuint*);
#endif
#if !defined(PFNGLPOLLINSTRUMENTSSGIXPROC)
typedef GLint(*PFNGLPOLLINSTRUMENTSSGIXPROC)(GLint*);
#endif
#if !defined(PFNGLRENDERMODEPROC)
typedef GLint(*PFNGLRENDERMODEPROC)(GLenum);
#endif
#if !defined(PFNGLGETUNIFORMOFFSETEXTPROC)
typedef GLintptr(*PFNGLGETUNIFORMOFFSETEXTPROC)(GLuint,GLint);
#endif
#if !defined(PFNGLCREATESYNCFROMCLEVENTARBPROC)
typedef GLsync(*PFNGLCREATESYNCFROMCLEVENTARBPROC)(struct _cl_context*,struct _cl_event*,GLbitfield);
#endif
#if !defined(PFNGLFENCESYNCPROC)
typedef GLsync(*PFNGLFENCESYNCPROC)(GLenum,GLbitfield);
#endif
#if !defined(PFNGLIMPORTSYNCEXTPROC)
typedef GLsync(*PFNGLIMPORTSYNCEXTPROC)(GLenum,GLintptr,GLbitfield);
#endif
#if !defined(PFNGLGETIMAGEHANDLEARBPROC)
typedef GLuint64(*PFNGLGETIMAGEHANDLEARBPROC)(GLuint,GLint,GLboolean,GLint,GLenum);
#endif
#if !defined(PFNGLGETIMAGEHANDLENVPROC)
typedef GLuint64(*PFNGLGETIMAGEHANDLENVPROC)(GLuint,GLint,GLboolean,GLint,GLenum);
#endif
#if !defined(PFNGLGETTEXTUREHANDLEARBPROC)
typedef GLuint64(*PFNGLGETTEXTUREHANDLEARBPROC)(GLuint);
#endif
#if !defined(PFNGLGETTEXTUREHANDLENVPROC)
typedef GLuint64(*PFNGLGETTEXTUREHANDLENVPROC)(GLuint);
#endif
#if !defined(PFNGLGETTEXTURESAMPLERHANDLEARBPROC)
typedef GLuint64(*PFNGLGETTEXTURESAMPLERHANDLEARBPROC)(GLuint,GLuint);
#endif
#if !defined(PFNGLGETTEXTURESAMPLERHANDLENVPROC)
typedef GLuint64(*PFNGLGETTEXTURESAMPLERHANDLENVPROC)(GLuint,GLuint);
#endif
#if !defined(PFNGLBINDLIGHTPARAMETEREXTPROC)
typedef GLuint(*PFNGLBINDLIGHTPARAMETEREXTPROC)(GLenum,GLenum);
#endif
#if !defined(PFNGLBINDMATERIALPARAMETEREXTPROC)
typedef GLuint(*PFNGLBINDMATERIALPARAMETEREXTPROC)(GLenum,GLenum);
#endif
#if !defined(PFNGLBINDPARAMETEREXTPROC)
typedef GLuint(*PFNGLBINDPARAMETEREXTPROC)(GLenum);
#endif
#if !defined(PFNGLBINDTEXGENPARAMETEREXTPROC)
typedef GLuint(*PFNGLBINDTEXGENPARAMETEREXTPROC)(GLenum,GLenum,GLenum);
#endif
#if !defined(PFNGLBINDTEXTUREUNITPARAMETEREXTPROC)
typedef GLuint(*PFNGLBINDTEXTUREUNITPARAMETEREXTPROC)(GLenum,GLenum);
#endif
#if !defined(PFNGLCREATEPROGRAMPROC)
typedef GLuint(*PFNGLCREATEPROGRAMPROC)();
#endif
#if !defined(PFNGLCREATESHADERPROC)
typedef GLuint(*PFNGLCREATESHADERPROC)(GLenum);
#endif
#if !defined(PFNGLCREATESHADERPROGRAMEXTPROC)
typedef GLuint(*PFNGLCREATESHADERPROGRAMEXTPROC)(GLenum,const GLchar*);
#endif
#if !defined(PFNGLCREATESHADERPROGRAMVPROC)
typedef GLuint(*PFNGLCREATESHADERPROGRAMVPROC)(GLenum,GLsizei,const GLchar*const*);
#endif
#if !defined(PFNGLGENASYNCMARKERSSGIXPROC)
typedef GLuint(*PFNGLGENASYNCMARKERSSGIXPROC)(GLsizei);
#endif
#if !defined(PFNGLGENFRAGMENTSHADERSATIPROC)
typedef GLuint(*PFNGLGENFRAGMENTSHADERSATIPROC)(GLuint);
#endif
#if !defined(PFNGLGENLISTSPROC)
typedef GLuint(*PFNGLGENLISTSPROC)(GLsizei);
#endif
#if !defined(PFNGLGENPATHSNVPROC)
typedef GLuint(*PFNGLGENPATHSNVPROC)(GLsizei);
#endif
#if !defined(PFNGLGENSYMBOLSEXTPROC)
typedef GLuint(*PFNGLGENSYMBOLSEXTPROC)(GLenum,GLenum,GLenum,GLuint);
#endif
#if !defined(PFNGLGENVERTEXSHADERSEXTPROC)
typedef GLuint(*PFNGLGENVERTEXSHADERSEXTPROC)(GLuint);
#endif
#if !defined(PFNGLGETCOMMANDHEADERNVPROC)
typedef GLuint(*PFNGLGETCOMMANDHEADERNVPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLGETDEBUGMESSAGELOGAMDPROC)
typedef GLuint(*PFNGLGETDEBUGMESSAGELOGAMDPROC)(GLuint,GLsizei,GLenum*,GLuint*,GLuint*,GLsizei*,GLchar*);
#endif
#if !defined(PFNGLGETDEBUGMESSAGELOGARBPROC)
typedef GLuint(*PFNGLGETDEBUGMESSAGELOGARBPROC)(GLuint,GLsizei,GLenum*,GLenum*,GLuint*,GLenum*,GLsizei*,GLchar*);
#endif
#if !defined(PFNGLGETDEBUGMESSAGELOGPROC)
typedef GLuint(*PFNGLGETDEBUGMESSAGELOGPROC)(GLuint,GLsizei,GLenum*,GLenum*,GLuint*,GLenum*,GLsizei*,GLchar*);
#endif
#if !defined(PFNGLGETPROGRAMRESOURCEINDEXPROC)
typedef GLuint(*PFNGLGETPROGRAMRESOURCEINDEXPROC)(GLuint,GLenum,const GLchar*);
#endif
#if !defined(PFNGLGETSUBROUTINEINDEXPROC)
typedef GLuint(*PFNGLGETSUBROUTINEINDEXPROC)(GLuint,GLenum,const GLchar*);
#endif
#if !defined(PFNGLGETUNIFORMBLOCKINDEXPROC)
typedef GLuint(*PFNGLGETUNIFORMBLOCKINDEXPROC)(GLuint,const GLchar*);
#endif
#if !defined(PFNGLNEWOBJECTBUFFERATIPROC)
typedef GLuint(*PFNGLNEWOBJECTBUFFERATIPROC)(GLsizei,const void*,GLenum);
#endif
#if !defined(PFNGLGETSTAGEINDEXNVPROC)
typedef GLushort(*PFNGLGETSTAGEINDEXNVPROC)(GLenum);
#endif
#if !defined(PFNGLVDPAUREGISTEROUTPUTSURFACENVPROC)
typedef GLvdpauSurfaceNV(*PFNGLVDPAUREGISTEROUTPUTSURFACENVPROC)(const void*,GLenum,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLVDPAUREGISTERVIDEOSURFACENVPROC)
typedef GLvdpauSurfaceNV(*PFNGLVDPAUREGISTERVIDEOSURFACENVPROC)(const void*,GLenum,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLACCUMPROC)
typedef void(*PFNGLACCUMPROC)(GLenum,GLfloat);
#endif
#if !defined(PFNGLACCUMXOESPROC)
typedef void(*PFNGLACCUMXOESPROC)(GLenum,GLfixed);
#endif
#if !defined(PFNGLACTIVEPROGRAMEXTPROC)
typedef void(*PFNGLACTIVEPROGRAMEXTPROC)(GLuint);
#endif
#if !defined(PFNGLACTIVESHADERPROGRAMPROC)
typedef void(*PFNGLACTIVESHADERPROGRAMPROC)(GLuint,GLuint);
#endif
#if !defined(PFNGLACTIVESTENCILFACEEXTPROC)
typedef void(*PFNGLACTIVESTENCILFACEEXTPROC)(GLenum);
#endif
#if !defined(PFNGLACTIVETEXTUREARBPROC)
typedef void(*PFNGLACTIVETEXTUREARBPROC)(GLenum);
#endif
#if !defined(PFNGLACTIVETEXTUREPROC)
typedef void(*PFNGLACTIVETEXTUREPROC)(GLenum);
#endif
#if !defined(PFNGLACTIVEVARYINGNVPROC)
typedef void(*PFNGLACTIVEVARYINGNVPROC)(GLuint,const GLchar*);
#endif
#if !defined(PFNGLALPHAFRAGMENTOP1ATIPROC)
typedef void(*PFNGLALPHAFRAGMENTOP1ATIPROC)(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLALPHAFRAGMENTOP2ATIPROC)
typedef void(*PFNGLALPHAFRAGMENTOP2ATIPROC)(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLALPHAFRAGMENTOP3ATIPROC)
typedef void(*PFNGLALPHAFRAGMENTOP3ATIPROC)(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLALPHAFUNCPROC)
typedef void(*PFNGLALPHAFUNCPROC)(GLenum,GLclampf);
#endif
#if !defined(PFNGLALPHAFUNCXOESPROC)
typedef void(*PFNGLALPHAFUNCXOESPROC)(GLenum,GLfixed);
#endif
#if !defined(PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC)
typedef void(*PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC)();
#endif
#if !defined(PFNGLAPPLYTEXTUREEXTPROC)
typedef void(*PFNGLAPPLYTEXTUREEXTPROC)(GLenum);
#endif
#if !defined(PFNGLARRAYELEMENTEXTPROC)
typedef void(*PFNGLARRAYELEMENTEXTPROC)(GLint);
#endif
#if !defined(PFNGLARRAYELEMENTPROC)
typedef void(*PFNGLARRAYELEMENTPROC)(GLint);
#endif
#if !defined(PFNGLARRAYOBJECTATIPROC)
typedef void(*PFNGLARRAYOBJECTATIPROC)(GLenum,GLint,GLenum,GLsizei,GLuint,GLuint);
#endif
#if !defined(PFNGLASYNCMARKERSGIXPROC)
typedef void(*PFNGLASYNCMARKERSGIXPROC)(GLuint);
#endif
#if !defined(PFNGLATTACHOBJECTARBPROC)
typedef void(*PFNGLATTACHOBJECTARBPROC)(GLhandleARB,GLhandleARB);
#endif
#if !defined(PFNGLATTACHSHADERPROC)
typedef void(*PFNGLATTACHSHADERPROC)(GLuint,GLuint);
#endif
#if !defined(PFNGLBEGINCONDITIONALRENDERPROC)
typedef void(*PFNGLBEGINCONDITIONALRENDERPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLBEGINCONDITIONALRENDERNVPROC)
typedef void(*PFNGLBEGINCONDITIONALRENDERNVPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLBEGINCONDITIONALRENDERNVXPROC)
typedef void(*PFNGLBEGINCONDITIONALRENDERNVXPROC)(GLuint);
#endif
#if !defined(PFNGLBEGINFRAGMENTSHADERATIPROC)
typedef void(*PFNGLBEGINFRAGMENTSHADERATIPROC)();
#endif
#if !defined(PFNGLBEGINPROC)
typedef void(*PFNGLBEGINPROC)(GLenum);
#endif
#if !defined(PFNGLBEGINOCCLUSIONQUERYNVPROC)
typedef void(*PFNGLBEGINOCCLUSIONQUERYNVPROC)(GLuint);
#endif
#if !defined(PFNGLBEGINPERFMONITORAMDPROC)
typedef void(*PFNGLBEGINPERFMONITORAMDPROC)(GLuint);
#endif
#if !defined(PFNGLBEGINPERFQUERYINTELPROC)
typedef void(*PFNGLBEGINPERFQUERYINTELPROC)(GLuint);
#endif
#if !defined(PFNGLBEGINQUERYARBPROC)
typedef void(*PFNGLBEGINQUERYARBPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLBEGINQUERYPROC)
typedef void(*PFNGLBEGINQUERYPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLBEGINQUERYINDEXEDPROC)
typedef void(*PFNGLBEGINQUERYINDEXEDPROC)(GLenum,GLuint,GLuint);
#endif
#if !defined(PFNGLBEGINTRANSFORMFEEDBACKEXTPROC)
typedef void(*PFNGLBEGINTRANSFORMFEEDBACKEXTPROC)(GLenum);
#endif
#if !defined(PFNGLBEGINTRANSFORMFEEDBACKPROC)
typedef void(*PFNGLBEGINTRANSFORMFEEDBACKPROC)(GLenum);
#endif
#if !defined(PFNGLBEGINTRANSFORMFEEDBACKNVPROC)
typedef void(*PFNGLBEGINTRANSFORMFEEDBACKNVPROC)(GLenum);
#endif
#if !defined(PFNGLBEGINVERTEXSHADEREXTPROC)
typedef void(*PFNGLBEGINVERTEXSHADEREXTPROC)();
#endif
#if !defined(PFNGLBEGINVIDEOCAPTURENVPROC)
typedef void(*PFNGLBEGINVIDEOCAPTURENVPROC)(GLuint);
#endif
#if !defined(PFNGLBINDATTRIBLOCATIONARBPROC)
typedef void(*PFNGLBINDATTRIBLOCATIONARBPROC)(GLhandleARB,GLuint,const GLcharARB*);
#endif
#if !defined(PFNGLBINDATTRIBLOCATIONPROC)
typedef void(*PFNGLBINDATTRIBLOCATIONPROC)(GLuint,GLuint,const GLchar*);
#endif
#if !defined(PFNGLBINDBUFFERARBPROC)
typedef void(*PFNGLBINDBUFFERARBPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLBINDBUFFERBASEEXTPROC)
typedef void(*PFNGLBINDBUFFERBASEEXTPROC)(GLenum,GLuint,GLuint);
#endif
#if !defined(PFNGLBINDBUFFERBASEPROC)
typedef void(*PFNGLBINDBUFFERBASEPROC)(GLenum,GLuint,GLuint);
#endif
#if !defined(PFNGLBINDBUFFERBASENVPROC)
typedef void(*PFNGLBINDBUFFERBASENVPROC)(GLenum,GLuint,GLuint);
#endif
#if !defined(PFNGLBINDBUFFERPROC)
typedef void(*PFNGLBINDBUFFERPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLBINDBUFFEROFFSETEXTPROC)
typedef void(*PFNGLBINDBUFFEROFFSETEXTPROC)(GLenum,GLuint,GLuint,GLintptr);
#endif
#if !defined(PFNGLBINDBUFFEROFFSETNVPROC)
typedef void(*PFNGLBINDBUFFEROFFSETNVPROC)(GLenum,GLuint,GLuint,GLintptr);
#endif
#if !defined(PFNGLBINDBUFFERRANGEEXTPROC)
typedef void(*PFNGLBINDBUFFERRANGEEXTPROC)(GLenum,GLuint,GLuint,GLintptr,GLsizeiptr);
#endif
#if !defined(PFNGLBINDBUFFERRANGEPROC)
typedef void(*PFNGLBINDBUFFERRANGEPROC)(GLenum,GLuint,GLuint,GLintptr,GLsizeiptr);
#endif
#if !defined(PFNGLBINDBUFFERRANGENVPROC)
typedef void(*PFNGLBINDBUFFERRANGENVPROC)(GLenum,GLuint,GLuint,GLintptr,GLsizeiptr);
#endif
#if !defined(PFNGLBINDBUFFERSBASEPROC)
typedef void(*PFNGLBINDBUFFERSBASEPROC)(GLenum,GLuint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLBINDBUFFERSRANGEPROC)
typedef void(*PFNGLBINDBUFFERSRANGEPROC)(GLenum,GLuint,GLsizei,const GLuint*,const GLintptr*,const GLsizeiptr*);
#endif
#if !defined(PFNGLBINDFRAGDATALOCATIONEXTPROC)
typedef void(*PFNGLBINDFRAGDATALOCATIONEXTPROC)(GLuint,GLuint,const GLchar*);
#endif
#if !defined(PFNGLBINDFRAGDATALOCATIONPROC)
typedef void(*PFNGLBINDFRAGDATALOCATIONPROC)(GLuint,GLuint,const GLchar*);
#endif
#if !defined(PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)
typedef void(*PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)(GLuint,GLuint,GLuint,const GLchar*);
#endif
#if !defined(PFNGLBINDFRAGMENTSHADERATIPROC)
typedef void(*PFNGLBINDFRAGMENTSHADERATIPROC)(GLuint);
#endif
#if !defined(PFNGLBINDFRAMEBUFFEREXTPROC)
typedef void(*PFNGLBINDFRAMEBUFFEREXTPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLBINDFRAMEBUFFERPROC)
typedef void(*PFNGLBINDFRAMEBUFFERPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLBINDIMAGETEXTUREEXTPROC)
typedef void(*PFNGLBINDIMAGETEXTUREEXTPROC)(GLuint,GLuint,GLint,GLboolean,GLint,GLenum,GLint);
#endif
#if !defined(PFNGLBINDIMAGETEXTUREPROC)
typedef void(*PFNGLBINDIMAGETEXTUREPROC)(GLuint,GLuint,GLint,GLboolean,GLint,GLenum,GLenum);
#endif
#if !defined(PFNGLBINDIMAGETEXTURESPROC)
typedef void(*PFNGLBINDIMAGETEXTURESPROC)(GLuint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLBINDMULTITEXTUREEXTPROC)
typedef void(*PFNGLBINDMULTITEXTUREEXTPROC)(GLenum,GLenum,GLuint);
#endif
#if !defined(PFNGLBINDPROGRAMARBPROC)
typedef void(*PFNGLBINDPROGRAMARBPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLBINDPROGRAMNVPROC)
typedef void(*PFNGLBINDPROGRAMNVPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLBINDPROGRAMPIPELINEPROC)
typedef void(*PFNGLBINDPROGRAMPIPELINEPROC)(GLuint);
#endif
#if !defined(PFNGLBINDRENDERBUFFEREXTPROC)
typedef void(*PFNGLBINDRENDERBUFFEREXTPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLBINDRENDERBUFFERPROC)
typedef void(*PFNGLBINDRENDERBUFFERPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLBINDSAMPLERPROC)
typedef void(*PFNGLBINDSAMPLERPROC)(GLuint,GLuint);
#endif
#if !defined(PFNGLBINDSAMPLERSPROC)
typedef void(*PFNGLBINDSAMPLERSPROC)(GLuint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLBINDTEXTUREEXTPROC)
typedef void(*PFNGLBINDTEXTUREEXTPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLBINDTEXTUREPROC)
typedef void(*PFNGLBINDTEXTUREPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLBINDTEXTURESPROC)
typedef void(*PFNGLBINDTEXTURESPROC)(GLuint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLBINDTEXTUREUNITPROC)
typedef void(*PFNGLBINDTEXTUREUNITPROC)(GLuint,GLuint);
#endif
#if !defined(PFNGLBINDTRANSFORMFEEDBACKPROC)
typedef void(*PFNGLBINDTRANSFORMFEEDBACKPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLBINDTRANSFORMFEEDBACKNVPROC)
typedef void(*PFNGLBINDTRANSFORMFEEDBACKNVPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLBINDVERTEXARRAYAPPLEPROC)
typedef void(*PFNGLBINDVERTEXARRAYAPPLEPROC)(GLuint);
#endif
#if !defined(PFNGLBINDVERTEXARRAYPROC)
typedef void(*PFNGLBINDVERTEXARRAYPROC)(GLuint);
#endif
#if !defined(PFNGLBINDVERTEXBUFFERPROC)
typedef void(*PFNGLBINDVERTEXBUFFERPROC)(GLuint,GLuint,GLintptr,GLsizei);
#endif
#if !defined(PFNGLBINDVERTEXBUFFERSPROC)
typedef void(*PFNGLBINDVERTEXBUFFERSPROC)(GLuint,GLsizei,const GLuint*,const GLintptr*,const GLsizei*);
#endif
#if !defined(PFNGLBINDVERTEXSHADEREXTPROC)
typedef void(*PFNGLBINDVERTEXSHADEREXTPROC)(GLuint);
#endif
#if !defined(PFNGLBINDVIDEOCAPTURESTREAMBUFFERNVPROC)
typedef void(*PFNGLBINDVIDEOCAPTURESTREAMBUFFERNVPROC)(GLuint,GLuint,GLenum,GLintptrARB);
#endif
#if !defined(PFNGLBINDVIDEOCAPTURESTREAMTEXTURENVPROC)
typedef void(*PFNGLBINDVIDEOCAPTURESTREAMTEXTURENVPROC)(GLuint,GLuint,GLenum,GLenum,GLuint);
#endif
#if !defined(PFNGLBINORMAL3BEXTPROC)
typedef void(*PFNGLBINORMAL3BEXTPROC)(GLbyte,GLbyte,GLbyte);
#endif
#if !defined(PFNGLBINORMAL3BVEXTPROC)
typedef void(*PFNGLBINORMAL3BVEXTPROC)(const GLbyte*);
#endif
#if !defined(PFNGLBINORMAL3DEXTPROC)
typedef void(*PFNGLBINORMAL3DEXTPROC)(GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLBINORMAL3DVEXTPROC)
typedef void(*PFNGLBINORMAL3DVEXTPROC)(const GLdouble*);
#endif
#if !defined(PFNGLBINORMAL3FEXTPROC)
typedef void(*PFNGLBINORMAL3FEXTPROC)(GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLBINORMAL3FVEXTPROC)
typedef void(*PFNGLBINORMAL3FVEXTPROC)(const GLfloat*);
#endif
#if !defined(PFNGLBINORMAL3IEXTPROC)
typedef void(*PFNGLBINORMAL3IEXTPROC)(GLint,GLint,GLint);
#endif
#if !defined(PFNGLBINORMAL3IVEXTPROC)
typedef void(*PFNGLBINORMAL3IVEXTPROC)(const GLint*);
#endif
#if !defined(PFNGLBINORMAL3SEXTPROC)
typedef void(*PFNGLBINORMAL3SEXTPROC)(GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLBINORMAL3SVEXTPROC)
typedef void(*PFNGLBINORMAL3SVEXTPROC)(const GLshort*);
#endif
#if !defined(PFNGLBINORMALPOINTEREXTPROC)
typedef void(*PFNGLBINORMALPOINTEREXTPROC)(GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLBITMAPPROC)
typedef void(*PFNGLBITMAPPROC)(GLsizei,GLsizei,GLfloat,GLfloat,GLfloat,GLfloat,const GLubyte*);
#endif
#if !defined(PFNGLBITMAPXOESPROC)
typedef void(*PFNGLBITMAPXOESPROC)(GLsizei,GLsizei,GLfixed,GLfixed,GLfixed,GLfixed,const GLubyte*);
#endif
#if !defined(PFNGLBLENDBARRIERKHRPROC)
typedef void(*PFNGLBLENDBARRIERKHRPROC)();
#endif
#if !defined(PFNGLBLENDBARRIERNVPROC)
typedef void(*PFNGLBLENDBARRIERNVPROC)();
#endif
#if !defined(PFNGLBLENDCOLOREXTPROC)
typedef void(*PFNGLBLENDCOLOREXTPROC)(GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLBLENDCOLORPROC)
typedef void(*PFNGLBLENDCOLORPROC)(GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLBLENDCOLORXOESPROC)
typedef void(*PFNGLBLENDCOLORXOESPROC)(GLfixed,GLfixed,GLfixed,GLfixed);
#endif
#if !defined(PFNGLBLENDEQUATIONEXTPROC)
typedef void(*PFNGLBLENDEQUATIONEXTPROC)(GLenum);
#endif
#if !defined(PFNGLBLENDEQUATIONPROC)
typedef void(*PFNGLBLENDEQUATIONPROC)(GLenum);
#endif
#if !defined(PFNGLBLENDEQUATIONIARBPROC)
typedef void(*PFNGLBLENDEQUATIONIARBPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLBLENDEQUATIONIPROC)
typedef void(*PFNGLBLENDEQUATIONIPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLBLENDEQUATIONINDEXEDAMDPROC)
typedef void(*PFNGLBLENDEQUATIONINDEXEDAMDPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLBLENDEQUATIONSEPARATEATIPROC)
typedef void(*PFNGLBLENDEQUATIONSEPARATEATIPROC)(GLenum,GLenum);
#endif
#if !defined(PFNGLBLENDEQUATIONSEPARATEEXTPROC)
typedef void(*PFNGLBLENDEQUATIONSEPARATEEXTPROC)(GLenum,GLenum);
#endif
#if !defined(PFNGLBLENDEQUATIONSEPARATEPROC)
typedef void(*PFNGLBLENDEQUATIONSEPARATEPROC)(GLenum,GLenum);
#endif
#if !defined(PFNGLBLENDEQUATIONSEPARATEIARBPROC)
typedef void(*PFNGLBLENDEQUATIONSEPARATEIARBPROC)(GLuint,GLenum,GLenum);
#endif
#if !defined(PFNGLBLENDEQUATIONSEPARATEIPROC)
typedef void(*PFNGLBLENDEQUATIONSEPARATEIPROC)(GLuint,GLenum,GLenum);
#endif
#if !defined(PFNGLBLENDEQUATIONSEPARATEINDEXEDAMDPROC)
typedef void(*PFNGLBLENDEQUATIONSEPARATEINDEXEDAMDPROC)(GLuint,GLenum,GLenum);
#endif
#if !defined(PFNGLBLENDFUNCPROC)
typedef void(*PFNGLBLENDFUNCPROC)(GLenum,GLenum);
#endif
#if !defined(PFNGLBLENDFUNCIARBPROC)
typedef void(*PFNGLBLENDFUNCIARBPROC)(GLuint,GLenum,GLenum);
#endif
#if !defined(PFNGLBLENDFUNCIPROC)
typedef void(*PFNGLBLENDFUNCIPROC)(GLuint,GLenum,GLenum);
#endif
#if !defined(PFNGLBLENDFUNCINDEXEDAMDPROC)
typedef void(*PFNGLBLENDFUNCINDEXEDAMDPROC)(GLuint,GLenum,GLenum);
#endif
#if !defined(PFNGLBLENDFUNCSEPARATEEXTPROC)
typedef void(*PFNGLBLENDFUNCSEPARATEEXTPROC)(GLenum,GLenum,GLenum,GLenum);
#endif
#if !defined(PFNGLBLENDFUNCSEPARATEPROC)
typedef void(*PFNGLBLENDFUNCSEPARATEPROC)(GLenum,GLenum,GLenum,GLenum);
#endif
#if !defined(PFNGLBLENDFUNCSEPARATEIARBPROC)
typedef void(*PFNGLBLENDFUNCSEPARATEIARBPROC)(GLuint,GLenum,GLenum,GLenum,GLenum);
#endif
#if !defined(PFNGLBLENDFUNCSEPARATEIPROC)
typedef void(*PFNGLBLENDFUNCSEPARATEIPROC)(GLuint,GLenum,GLenum,GLenum,GLenum);
#endif
#if !defined(PFNGLBLENDFUNCSEPARATEINDEXEDAMDPROC)
typedef void(*PFNGLBLENDFUNCSEPARATEINDEXEDAMDPROC)(GLuint,GLenum,GLenum,GLenum,GLenum);
#endif
#if !defined(PFNGLBLENDFUNCSEPARATEINGRPROC)
typedef void(*PFNGLBLENDFUNCSEPARATEINGRPROC)(GLenum,GLenum,GLenum,GLenum);
#endif
#if !defined(PFNGLBLENDPARAMETERINVPROC)
typedef void(*PFNGLBLENDPARAMETERINVPROC)(GLenum,GLint);
#endif
#if !defined(PFNGLBLITFRAMEBUFFEREXTPROC)
typedef void(*PFNGLBLITFRAMEBUFFEREXTPROC)(GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLbitfield,GLenum);
#endif
#if !defined(PFNGLBLITFRAMEBUFFERPROC)
typedef void(*PFNGLBLITFRAMEBUFFERPROC)(GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLbitfield,GLenum);
#endif
#if !defined(PFNGLBLITNAMEDFRAMEBUFFERPROC)
typedef void(*PFNGLBLITNAMEDFRAMEBUFFERPROC)(GLuint,GLuint,GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLbitfield,GLenum);
#endif
#if !defined(PFNGLBUFFERADDRESSRANGENVPROC)
typedef void(*PFNGLBUFFERADDRESSRANGENVPROC)(GLenum,GLuint,GLuint64EXT,GLsizeiptr);
#endif
#if !defined(PFNGLBUFFERDATAARBPROC)
typedef void(*PFNGLBUFFERDATAARBPROC)(GLenum,GLsizeiptrARB,const void*,GLenum);
#endif
#if !defined(PFNGLBUFFERDATAPROC)
typedef void(*PFNGLBUFFERDATAPROC)(GLenum,GLsizeiptr,const void*,GLenum);
#endif
#if !defined(PFNGLBUFFERPAGECOMMITMENTARBPROC)
typedef void(*PFNGLBUFFERPAGECOMMITMENTARBPROC)(GLenum,GLintptr,GLsizeiptr,GLboolean);
#endif
#if !defined(PFNGLBUFFERPARAMETERIAPPLEPROC)
typedef void(*PFNGLBUFFERPARAMETERIAPPLEPROC)(GLenum,GLenum,GLint);
#endif
#if !defined(PFNGLBUFFERSTORAGEPROC)
typedef void(*PFNGLBUFFERSTORAGEPROC)(GLenum,GLsizeiptr,const void*,GLbitfield);
#endif
#if !defined(PFNGLBUFFERSUBDATAARBPROC)
typedef void(*PFNGLBUFFERSUBDATAARBPROC)(GLenum,GLintptrARB,GLsizeiptrARB,const void*);
#endif
#if !defined(PFNGLBUFFERSUBDATAPROC)
typedef void(*PFNGLBUFFERSUBDATAPROC)(GLenum,GLintptr,GLsizeiptr,const void*);
#endif
#if !defined(PFNGLCALLCOMMANDLISTNVPROC)
typedef void(*PFNGLCALLCOMMANDLISTNVPROC)(GLuint);
#endif
#if !defined(PFNGLCALLLISTPROC)
typedef void(*PFNGLCALLLISTPROC)(GLuint);
#endif
#if !defined(PFNGLCALLLISTSPROC)
typedef void(*PFNGLCALLLISTSPROC)(GLsizei,GLenum,const GLvoid*);
#endif
#if !defined(PFNGLCLAMPCOLORARBPROC)
typedef void(*PFNGLCLAMPCOLORARBPROC)(GLenum,GLenum);
#endif
#if !defined(PFNGLCLAMPCOLORPROC)
typedef void(*PFNGLCLAMPCOLORPROC)(GLenum,GLenum);
#endif
#if !defined(PFNGLCLEARACCUMPROC)
typedef void(*PFNGLCLEARACCUMPROC)(GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLCLEARACCUMXOESPROC)
typedef void(*PFNGLCLEARACCUMXOESPROC)(GLfixed,GLfixed,GLfixed,GLfixed);
#endif
#if !defined(PFNGLCLEARBUFFERDATAPROC)
typedef void(*PFNGLCLEARBUFFERDATAPROC)(GLenum,GLenum,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLCLEARBUFFERFIPROC)
typedef void(*PFNGLCLEARBUFFERFIPROC)(GLenum,GLint,GLfloat,GLint);
#endif
#if !defined(PFNGLCLEARBUFFERFVPROC)
typedef void(*PFNGLCLEARBUFFERFVPROC)(GLenum,GLint,const GLfloat*);
#endif
#if !defined(PFNGLCLEARBUFFERIVPROC)
typedef void(*PFNGLCLEARBUFFERIVPROC)(GLenum,GLint,const GLint*);
#endif
#if !defined(PFNGLCLEARBUFFERSUBDATAPROC)
typedef void(*PFNGLCLEARBUFFERSUBDATAPROC)(GLenum,GLenum,GLintptr,GLsizeiptr,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLCLEARBUFFERUIVPROC)
typedef void(*PFNGLCLEARBUFFERUIVPROC)(GLenum,GLint,const GLuint*);
#endif
#if !defined(PFNGLCLEARCOLORPROC)
typedef void(*PFNGLCLEARCOLORPROC)(GLclampf,GLclampf,GLclampf,GLclampf);
#endif
#if !defined(PFNGLCLEARCOLORIIEXTPROC)
typedef void(*PFNGLCLEARCOLORIIEXTPROC)(GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLCLEARCOLORIUIEXTPROC)
typedef void(*PFNGLCLEARCOLORIUIEXTPROC)(GLuint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLCLEARCOLORXOESPROC)
typedef void(*PFNGLCLEARCOLORXOESPROC)(GLfixed,GLfixed,GLfixed,GLfixed);
#endif
#if !defined(PFNGLCLEARDEPTHDNVPROC)
typedef void(*PFNGLCLEARDEPTHDNVPROC)(GLdouble);
#endif
#if !defined(PFNGLCLEARDEPTHFPROC)
typedef void(*PFNGLCLEARDEPTHFPROC)(GLfloat);
#endif
#if !defined(PFNGLCLEARDEPTHFOESPROC)
typedef void(*PFNGLCLEARDEPTHFOESPROC)(GLclampf);
#endif
#if !defined(PFNGLCLEARDEPTHPROC)
typedef void(*PFNGLCLEARDEPTHPROC)(GLclampd);
#endif
#if !defined(PFNGLCLEARDEPTHXOESPROC)
typedef void(*PFNGLCLEARDEPTHXOESPROC)(GLfixed);
#endif
#if !defined(PFNGLCLEARPROC)
typedef void(*PFNGLCLEARPROC)(GLbitfield);
#endif
#if !defined(PFNGLCLEARINDEXPROC)
typedef void(*PFNGLCLEARINDEXPROC)(GLfloat);
#endif
#if !defined(PFNGLCLEARNAMEDBUFFERDATAEXTPROC)
typedef void(*PFNGLCLEARNAMEDBUFFERDATAEXTPROC)(GLuint,GLenum,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLCLEARNAMEDBUFFERDATAPROC)
typedef void(*PFNGLCLEARNAMEDBUFFERDATAPROC)(GLuint,GLenum,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLCLEARNAMEDBUFFERSUBDATAEXTPROC)
typedef void(*PFNGLCLEARNAMEDBUFFERSUBDATAEXTPROC)(GLuint,GLenum,GLsizeiptr,GLsizeiptr,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLCLEARNAMEDBUFFERSUBDATAPROC)
typedef void(*PFNGLCLEARNAMEDBUFFERSUBDATAPROC)(GLuint,GLenum,GLintptr,GLsizeiptr,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLCLEARNAMEDFRAMEBUFFERFIPROC)
typedef void(*PFNGLCLEARNAMEDFRAMEBUFFERFIPROC)(GLuint,GLenum,GLint,GLfloat,GLint);
#endif
#if !defined(PFNGLCLEARNAMEDFRAMEBUFFERFVPROC)
typedef void(*PFNGLCLEARNAMEDFRAMEBUFFERFVPROC)(GLuint,GLenum,GLint,const GLfloat*);
#endif
#if !defined(PFNGLCLEARNAMEDFRAMEBUFFERIVPROC)
typedef void(*PFNGLCLEARNAMEDFRAMEBUFFERIVPROC)(GLuint,GLenum,GLint,const GLint*);
#endif
#if !defined(PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC)
typedef void(*PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC)(GLuint,GLenum,GLint,const GLuint*);
#endif
#if !defined(PFNGLCLEARSTENCILPROC)
typedef void(*PFNGLCLEARSTENCILPROC)(GLint);
#endif
#if !defined(PFNGLCLEARTEXIMAGEPROC)
typedef void(*PFNGLCLEARTEXIMAGEPROC)(GLuint,GLint,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLCLEARTEXSUBIMAGEPROC)
typedef void(*PFNGLCLEARTEXSUBIMAGEPROC)(GLuint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLCLIENTACTIVETEXTUREARBPROC)
typedef void(*PFNGLCLIENTACTIVETEXTUREARBPROC)(GLenum);
#endif
#if !defined(PFNGLCLIENTACTIVETEXTUREPROC)
typedef void(*PFNGLCLIENTACTIVETEXTUREPROC)(GLenum);
#endif
#if !defined(PFNGLCLIENTACTIVEVERTEXSTREAMATIPROC)
typedef void(*PFNGLCLIENTACTIVEVERTEXSTREAMATIPROC)(GLenum);
#endif
#if !defined(PFNGLCLIENTATTRIBDEFAULTEXTPROC)
typedef void(*PFNGLCLIENTATTRIBDEFAULTEXTPROC)(GLbitfield);
#endif
#if !defined(PFNGLCLIPCONTROLPROC)
typedef void(*PFNGLCLIPCONTROLPROC)(GLenum,GLenum);
#endif
#if !defined(PFNGLCLIPPLANEFOESPROC)
typedef void(*PFNGLCLIPPLANEFOESPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLCLIPPLANEPROC)
typedef void(*PFNGLCLIPPLANEPROC)(GLenum,const GLdouble*);
#endif
#if !defined(PFNGLCLIPPLANEXOESPROC)
typedef void(*PFNGLCLIPPLANEXOESPROC)(GLenum,const GLfixed*);
#endif
#if !defined(PFNGLCOLOR3BPROC)
typedef void(*PFNGLCOLOR3BPROC)(GLbyte,GLbyte,GLbyte);
#endif
#if !defined(PFNGLCOLOR3BVPROC)
typedef void(*PFNGLCOLOR3BVPROC)(const GLbyte*);
#endif
#if !defined(PFNGLCOLOR3DPROC)
typedef void(*PFNGLCOLOR3DPROC)(GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLCOLOR3DVPROC)
typedef void(*PFNGLCOLOR3DVPROC)(const GLdouble*);
#endif
#if !defined(PFNGLCOLOR3FPROC)
typedef void(*PFNGLCOLOR3FPROC)(GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLCOLOR3FVPROC)
typedef void(*PFNGLCOLOR3FVPROC)(const GLfloat*);
#endif
#if !defined(PFNGLCOLOR3FVERTEX3FSUNPROC)
typedef void(*PFNGLCOLOR3FVERTEX3FSUNPROC)(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLCOLOR3FVERTEX3FVSUNPROC)
typedef void(*PFNGLCOLOR3FVERTEX3FVSUNPROC)(const GLfloat*,const GLfloat*);
#endif
#if !defined(PFNGLCOLOR3HNVPROC)
typedef void(*PFNGLCOLOR3HNVPROC)(GLhalfNV,GLhalfNV,GLhalfNV);
#endif
#if !defined(PFNGLCOLOR3HVNVPROC)
typedef void(*PFNGLCOLOR3HVNVPROC)(const GLhalfNV*);
#endif
#if !defined(PFNGLCOLOR3IPROC)
typedef void(*PFNGLCOLOR3IPROC)(GLint,GLint,GLint);
#endif
#if !defined(PFNGLCOLOR3IVPROC)
typedef void(*PFNGLCOLOR3IVPROC)(const GLint*);
#endif
#if !defined(PFNGLCOLOR3SPROC)
typedef void(*PFNGLCOLOR3SPROC)(GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLCOLOR3SVPROC)
typedef void(*PFNGLCOLOR3SVPROC)(const GLshort*);
#endif
#if !defined(PFNGLCOLOR3UBPROC)
typedef void(*PFNGLCOLOR3UBPROC)(GLubyte,GLubyte,GLubyte);
#endif
#if !defined(PFNGLCOLOR3UBVPROC)
typedef void(*PFNGLCOLOR3UBVPROC)(const GLubyte*);
#endif
#if !defined(PFNGLCOLOR3UIPROC)
typedef void(*PFNGLCOLOR3UIPROC)(GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLCOLOR3UIVPROC)
typedef void(*PFNGLCOLOR3UIVPROC)(const GLuint*);
#endif
#if !defined(PFNGLCOLOR3USPROC)
typedef void(*PFNGLCOLOR3USPROC)(GLushort,GLushort,GLushort);
#endif
#if !defined(PFNGLCOLOR3USVPROC)
typedef void(*PFNGLCOLOR3USVPROC)(const GLushort*);
#endif
#if !defined(PFNGLCOLOR3XOESPROC)
typedef void(*PFNGLCOLOR3XOESPROC)(GLfixed,GLfixed,GLfixed);
#endif
#if !defined(PFNGLCOLOR3XVOESPROC)
typedef void(*PFNGLCOLOR3XVOESPROC)(const GLfixed*);
#endif
#if !defined(PFNGLCOLOR4BPROC)
typedef void(*PFNGLCOLOR4BPROC)(GLbyte,GLbyte,GLbyte,GLbyte);
#endif
#if !defined(PFNGLCOLOR4BVPROC)
typedef void(*PFNGLCOLOR4BVPROC)(const GLbyte*);
#endif
#if !defined(PFNGLCOLOR4DPROC)
typedef void(*PFNGLCOLOR4DPROC)(GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLCOLOR4DVPROC)
typedef void(*PFNGLCOLOR4DVPROC)(const GLdouble*);
#endif
#if !defined(PFNGLCOLOR4FPROC)
typedef void(*PFNGLCOLOR4FPROC)(GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLCOLOR4FNORMAL3FVERTEX3FSUNPROC)
typedef void(*PFNGLCOLOR4FNORMAL3FVERTEX3FSUNPROC)(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLCOLOR4FNORMAL3FVERTEX3FVSUNPROC)
typedef void(*PFNGLCOLOR4FNORMAL3FVERTEX3FVSUNPROC)(const GLfloat*,const GLfloat*,const GLfloat*);
#endif
#if !defined(PFNGLCOLOR4FVPROC)
typedef void(*PFNGLCOLOR4FVPROC)(const GLfloat*);
#endif
#if !defined(PFNGLCOLOR4HNVPROC)
typedef void(*PFNGLCOLOR4HNVPROC)(GLhalfNV,GLhalfNV,GLhalfNV,GLhalfNV);
#endif
#if !defined(PFNGLCOLOR4HVNVPROC)
typedef void(*PFNGLCOLOR4HVNVPROC)(const GLhalfNV*);
#endif
#if !defined(PFNGLCOLOR4IPROC)
typedef void(*PFNGLCOLOR4IPROC)(GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLCOLOR4IVPROC)
typedef void(*PFNGLCOLOR4IVPROC)(const GLint*);
#endif
#if !defined(PFNGLCOLOR4SPROC)
typedef void(*PFNGLCOLOR4SPROC)(GLshort,GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLCOLOR4SVPROC)
typedef void(*PFNGLCOLOR4SVPROC)(const GLshort*);
#endif
#if !defined(PFNGLCOLOR4UBPROC)
typedef void(*PFNGLCOLOR4UBPROC)(GLubyte,GLubyte,GLubyte,GLubyte);
#endif
#if !defined(PFNGLCOLOR4UBVPROC)
typedef void(*PFNGLCOLOR4UBVPROC)(const GLubyte*);
#endif
#if !defined(PFNGLCOLOR4UBVERTEX2FSUNPROC)
typedef void(*PFNGLCOLOR4UBVERTEX2FSUNPROC)(GLubyte,GLubyte,GLubyte,GLubyte,GLfloat,GLfloat);
#endif
#if !defined(PFNGLCOLOR4UBVERTEX2FVSUNPROC)
typedef void(*PFNGLCOLOR4UBVERTEX2FVSUNPROC)(const GLubyte*,const GLfloat*);
#endif
#if !defined(PFNGLCOLOR4UBVERTEX3FSUNPROC)
typedef void(*PFNGLCOLOR4UBVERTEX3FSUNPROC)(GLubyte,GLubyte,GLubyte,GLubyte,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLCOLOR4UBVERTEX3FVSUNPROC)
typedef void(*PFNGLCOLOR4UBVERTEX3FVSUNPROC)(const GLubyte*,const GLfloat*);
#endif
#if !defined(PFNGLCOLOR4UIPROC)
typedef void(*PFNGLCOLOR4UIPROC)(GLuint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLCOLOR4UIVPROC)
typedef void(*PFNGLCOLOR4UIVPROC)(const GLuint*);
#endif
#if !defined(PFNGLCOLOR4USPROC)
typedef void(*PFNGLCOLOR4USPROC)(GLushort,GLushort,GLushort,GLushort);
#endif
#if !defined(PFNGLCOLOR4USVPROC)
typedef void(*PFNGLCOLOR4USVPROC)(const GLushort*);
#endif
#if !defined(PFNGLCOLOR4XOESPROC)
typedef void(*PFNGLCOLOR4XOESPROC)(GLfixed,GLfixed,GLfixed,GLfixed);
#endif
#if !defined(PFNGLCOLOR4XVOESPROC)
typedef void(*PFNGLCOLOR4XVOESPROC)(const GLfixed*);
#endif
#if !defined(PFNGLCOLORFORMATNVPROC)
typedef void(*PFNGLCOLORFORMATNVPROC)(GLint,GLenum,GLsizei);
#endif
#if !defined(PFNGLCOLORFRAGMENTOP1ATIPROC)
typedef void(*PFNGLCOLORFRAGMENTOP1ATIPROC)(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLCOLORFRAGMENTOP2ATIPROC)
typedef void(*PFNGLCOLORFRAGMENTOP2ATIPROC)(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLCOLORFRAGMENTOP3ATIPROC)
typedef void(*PFNGLCOLORFRAGMENTOP3ATIPROC)(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLCOLORMASKPROC)
typedef void(*PFNGLCOLORMASKPROC)(GLboolean,GLboolean,GLboolean,GLboolean);
#endif
#if !defined(PFNGLCOLORMASKIPROC)
typedef void(*PFNGLCOLORMASKIPROC)(GLuint,GLboolean,GLboolean,GLboolean,GLboolean);
#endif
#if !defined(PFNGLCOLORMASKINDEXEDEXTPROC)
typedef void(*PFNGLCOLORMASKINDEXEDEXTPROC)(GLuint,GLboolean,GLboolean,GLboolean,GLboolean);
#endif
#if !defined(PFNGLCOLORMATERIALPROC)
typedef void(*PFNGLCOLORMATERIALPROC)(GLenum,GLenum);
#endif
#if !defined(PFNGLCOLORP3UIPROC)
typedef void(*PFNGLCOLORP3UIPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLCOLORP3UIVPROC)
typedef void(*PFNGLCOLORP3UIVPROC)(GLenum,const GLuint*);
#endif
#if !defined(PFNGLCOLORP4UIPROC)
typedef void(*PFNGLCOLORP4UIPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLCOLORP4UIVPROC)
typedef void(*PFNGLCOLORP4UIVPROC)(GLenum,const GLuint*);
#endif
#if !defined(PFNGLCOLORPOINTEREXTPROC)
typedef void(*PFNGLCOLORPOINTEREXTPROC)(GLint,GLenum,GLsizei,GLsizei,const void*);
#endif
#if !defined(PFNGLCOLORPOINTERPROC)
typedef void(*PFNGLCOLORPOINTERPROC)(GLint,GLenum,GLsizei,const GLvoid*);
#endif
#if !defined(PFNGLCOLORPOINTERLISTIBMPROC)
typedef void(*PFNGLCOLORPOINTERLISTIBMPROC)(GLint,GLenum,GLint,const void**,GLint);
#endif
#if !defined(PFNGLCOLORPOINTERVINTELPROC)
typedef void(*PFNGLCOLORPOINTERVINTELPROC)(GLint,GLenum,const void**);
#endif
#if !defined(PFNGLCOLORSUBTABLEEXTPROC)
typedef void(*PFNGLCOLORSUBTABLEEXTPROC)(GLenum,GLsizei,GLsizei,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLCOLORSUBTABLEPROC)
typedef void(*PFNGLCOLORSUBTABLEPROC)(GLenum,GLsizei,GLsizei,GLenum,GLenum,const GLvoid*);
#endif
#if !defined(PFNGLCOLORTABLEEXTPROC)
typedef void(*PFNGLCOLORTABLEEXTPROC)(GLenum,GLenum,GLsizei,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLCOLORTABLEPROC)
typedef void(*PFNGLCOLORTABLEPROC)(GLenum,GLenum,GLsizei,GLenum,GLenum,const GLvoid*);
#endif
#if !defined(PFNGLCOLORTABLEPARAMETERFVPROC)
typedef void(*PFNGLCOLORTABLEPARAMETERFVPROC)(GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLCOLORTABLEPARAMETERFVSGIPROC)
typedef void(*PFNGLCOLORTABLEPARAMETERFVSGIPROC)(GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLCOLORTABLEPARAMETERIVPROC)
typedef void(*PFNGLCOLORTABLEPARAMETERIVPROC)(GLenum,GLenum,const GLint*);
#endif
#if !defined(PFNGLCOLORTABLEPARAMETERIVSGIPROC)
typedef void(*PFNGLCOLORTABLEPARAMETERIVSGIPROC)(GLenum,GLenum,const GLint*);
#endif
#if !defined(PFNGLCOLORTABLESGIPROC)
typedef void(*PFNGLCOLORTABLESGIPROC)(GLenum,GLenum,GLsizei,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLCOMBINERINPUTNVPROC)
typedef void(*PFNGLCOMBINERINPUTNVPROC)(GLenum,GLenum,GLenum,GLenum,GLenum,GLenum);
#endif
#if !defined(PFNGLCOMBINEROUTPUTNVPROC)
typedef void(*PFNGLCOMBINEROUTPUTNVPROC)(GLenum,GLenum,GLenum,GLenum,GLenum,GLenum,GLenum,GLboolean,GLboolean,GLboolean);
#endif
#if !defined(PFNGLCOMBINERPARAMETERFNVPROC)
typedef void(*PFNGLCOMBINERPARAMETERFNVPROC)(GLenum,GLfloat);
#endif
#if !defined(PFNGLCOMBINERPARAMETERFVNVPROC)
typedef void(*PFNGLCOMBINERPARAMETERFVNVPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLCOMBINERPARAMETERINVPROC)
typedef void(*PFNGLCOMBINERPARAMETERINVPROC)(GLenum,GLint);
#endif
#if !defined(PFNGLCOMBINERPARAMETERIVNVPROC)
typedef void(*PFNGLCOMBINERPARAMETERIVNVPROC)(GLenum,const GLint*);
#endif
#if !defined(PFNGLCOMBINERSTAGEPARAMETERFVNVPROC)
typedef void(*PFNGLCOMBINERSTAGEPARAMETERFVNVPROC)(GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLCOMMANDLISTSEGMENTSNVPROC)
typedef void(*PFNGLCOMMANDLISTSEGMENTSNVPROC)(GLuint,GLuint);
#endif
#if !defined(PFNGLCOMPILECOMMANDLISTNVPROC)
typedef void(*PFNGLCOMPILECOMMANDLISTNVPROC)(GLuint);
#endif
#if !defined(PFNGLCOMPILESHADERARBPROC)
typedef void(*PFNGLCOMPILESHADERARBPROC)(GLhandleARB);
#endif
#if !defined(PFNGLCOMPILESHADERPROC)
typedef void(*PFNGLCOMPILESHADERPROC)(GLuint);
#endif
#if !defined(PFNGLCOMPILESHADERINCLUDEARBPROC)
typedef void(*PFNGLCOMPILESHADERINCLUDEARBPROC)(GLuint,GLsizei,const GLchar*const*,const GLint*);
#endif
#if !defined(PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC)
typedef void(*PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC)(GLenum,GLenum,GLint,GLenum,GLsizei,GLint,GLsizei,const void*);
#endif
#if !defined(PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC)
typedef void(*PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC)(GLenum,GLenum,GLint,GLenum,GLsizei,GLsizei,GLint,GLsizei,const void*);
#endif
#if !defined(PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC)
typedef void(*PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC)(GLenum,GLenum,GLint,GLenum,GLsizei,GLsizei,GLsizei,GLint,GLsizei,const void*);
#endif
#if !defined(PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC)
typedef void(*PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC)(GLenum,GLenum,GLint,GLint,GLsizei,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC)
typedef void(*PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC)(GLenum,GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC)
typedef void(*PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC)(GLenum,GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLCOMPRESSEDTEXIMAGE1DARBPROC)
typedef void(*PFNGLCOMPRESSEDTEXIMAGE1DARBPROC)(GLenum,GLint,GLenum,GLsizei,GLint,GLsizei,const void*);
#endif
#if !defined(PFNGLCOMPRESSEDTEXIMAGE1DPROC)
typedef void(*PFNGLCOMPRESSEDTEXIMAGE1DPROC)(GLenum,GLint,GLenum,GLsizei,GLint,GLsizei,const GLvoid*);
#endif
#if !defined(PFNGLCOMPRESSEDTEXIMAGE2DARBPROC)
typedef void(*PFNGLCOMPRESSEDTEXIMAGE2DARBPROC)(GLenum,GLint,GLenum,GLsizei,GLsizei,GLint,GLsizei,const void*);
#endif
#if !defined(PFNGLCOMPRESSEDTEXIMAGE2DPROC)
typedef void(*PFNGLCOMPRESSEDTEXIMAGE2DPROC)(GLenum,GLint,GLenum,GLsizei,GLsizei,GLint,GLsizei,const GLvoid*);
#endif
#if !defined(PFNGLCOMPRESSEDTEXIMAGE3DARBPROC)
typedef void(*PFNGLCOMPRESSEDTEXIMAGE3DARBPROC)(GLenum,GLint,GLenum,GLsizei,GLsizei,GLsizei,GLint,GLsizei,const void*);
#endif
#if !defined(PFNGLCOMPRESSEDTEXIMAGE3DPROC)
typedef void(*PFNGLCOMPRESSEDTEXIMAGE3DPROC)(GLenum,GLint,GLenum,GLsizei,GLsizei,GLsizei,GLint,GLsizei,const GLvoid*);
#endif
#if !defined(PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC)
typedef void(*PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC)(GLenum,GLint,GLint,GLsizei,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)
typedef void(*PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)(GLenum,GLint,GLint,GLsizei,GLenum,GLsizei,const GLvoid*);
#endif
#if !defined(PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC)
typedef void(*PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC)(GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)
typedef void(*PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)(GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLsizei,const GLvoid*);
#endif
#if !defined(PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC)
typedef void(*PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC)(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)
typedef void(*PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLsizei,const GLvoid*);
#endif
#if !defined(PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC)
typedef void(*PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC)(GLuint,GLenum,GLint,GLenum,GLsizei,GLint,GLsizei,const void*);
#endif
#if !defined(PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC)
typedef void(*PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC)(GLuint,GLenum,GLint,GLenum,GLsizei,GLsizei,GLint,GLsizei,const void*);
#endif
#if !defined(PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC)
typedef void(*PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC)(GLuint,GLenum,GLint,GLenum,GLsizei,GLsizei,GLsizei,GLint,GLsizei,const void*);
#endif
#if !defined(PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC)
typedef void(*PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC)(GLuint,GLenum,GLint,GLint,GLsizei,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC)
typedef void(*PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC)(GLuint,GLint,GLint,GLsizei,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC)
typedef void(*PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC)(GLuint,GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC)
typedef void(*PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC)(GLuint,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC)
typedef void(*PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC)(GLuint,GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC)
typedef void(*PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC)(GLuint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLCONSERVATIVERASTERPARAMETERFNVPROC)
typedef void(*PFNGLCONSERVATIVERASTERPARAMETERFNVPROC)(GLenum,GLfloat);
#endif
#if !defined(PFNGLCONVOLUTIONFILTER1DEXTPROC)
typedef void(*PFNGLCONVOLUTIONFILTER1DEXTPROC)(GLenum,GLenum,GLsizei,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLCONVOLUTIONFILTER1DPROC)
typedef void(*PFNGLCONVOLUTIONFILTER1DPROC)(GLenum,GLenum,GLsizei,GLenum,GLenum,const GLvoid*);
#endif
#if !defined(PFNGLCONVOLUTIONFILTER2DEXTPROC)
typedef void(*PFNGLCONVOLUTIONFILTER2DEXTPROC)(GLenum,GLenum,GLsizei,GLsizei,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLCONVOLUTIONFILTER2DPROC)
typedef void(*PFNGLCONVOLUTIONFILTER2DPROC)(GLenum,GLenum,GLsizei,GLsizei,GLenum,GLenum,const GLvoid*);
#endif
#if !defined(PFNGLCONVOLUTIONPARAMETERFEXTPROC)
typedef void(*PFNGLCONVOLUTIONPARAMETERFEXTPROC)(GLenum,GLenum,GLfloat);
#endif
#if !defined(PFNGLCONVOLUTIONPARAMETERFPROC)
typedef void(*PFNGLCONVOLUTIONPARAMETERFPROC)(GLenum,GLenum,GLfloat);
#endif
#if !defined(PFNGLCONVOLUTIONPARAMETERFVEXTPROC)
typedef void(*PFNGLCONVOLUTIONPARAMETERFVEXTPROC)(GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLCONVOLUTIONPARAMETERFVPROC)
typedef void(*PFNGLCONVOLUTIONPARAMETERFVPROC)(GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLCONVOLUTIONPARAMETERIEXTPROC)
typedef void(*PFNGLCONVOLUTIONPARAMETERIEXTPROC)(GLenum,GLenum,GLint);
#endif
#if !defined(PFNGLCONVOLUTIONPARAMETERIPROC)
typedef void(*PFNGLCONVOLUTIONPARAMETERIPROC)(GLenum,GLenum,GLint);
#endif
#if !defined(PFNGLCONVOLUTIONPARAMETERIVEXTPROC)
typedef void(*PFNGLCONVOLUTIONPARAMETERIVEXTPROC)(GLenum,GLenum,const GLint*);
#endif
#if !defined(PFNGLCONVOLUTIONPARAMETERIVPROC)
typedef void(*PFNGLCONVOLUTIONPARAMETERIVPROC)(GLenum,GLenum,const GLint*);
#endif
#if !defined(PFNGLCONVOLUTIONPARAMETERXOESPROC)
typedef void(*PFNGLCONVOLUTIONPARAMETERXOESPROC)(GLenum,GLenum,GLfixed);
#endif
#if !defined(PFNGLCONVOLUTIONPARAMETERXVOESPROC)
typedef void(*PFNGLCONVOLUTIONPARAMETERXVOESPROC)(GLenum,GLenum,const GLfixed*);
#endif
#if !defined(PFNGLCOPYBUFFERSUBDATAPROC)
typedef void(*PFNGLCOPYBUFFERSUBDATAPROC)(GLenum,GLenum,GLintptr,GLintptr,GLsizeiptr);
#endif
#if !defined(PFNGLCOPYCOLORSUBTABLEEXTPROC)
typedef void(*PFNGLCOPYCOLORSUBTABLEEXTPROC)(GLenum,GLsizei,GLint,GLint,GLsizei);
#endif
#if !defined(PFNGLCOPYCOLORSUBTABLEPROC)
typedef void(*PFNGLCOPYCOLORSUBTABLEPROC)(GLenum,GLsizei,GLint,GLint,GLsizei);
#endif
#if !defined(PFNGLCOPYCOLORTABLEPROC)
typedef void(*PFNGLCOPYCOLORTABLEPROC)(GLenum,GLenum,GLint,GLint,GLsizei);
#endif
#if !defined(PFNGLCOPYCOLORTABLESGIPROC)
typedef void(*PFNGLCOPYCOLORTABLESGIPROC)(GLenum,GLenum,GLint,GLint,GLsizei);
#endif
#if !defined(PFNGLCOPYCONVOLUTIONFILTER1DEXTPROC)
typedef void(*PFNGLCOPYCONVOLUTIONFILTER1DEXTPROC)(GLenum,GLenum,GLint,GLint,GLsizei);
#endif
#if !defined(PFNGLCOPYCONVOLUTIONFILTER1DPROC)
typedef void(*PFNGLCOPYCONVOLUTIONFILTER1DPROC)(GLenum,GLenum,GLint,GLint,GLsizei);
#endif
#if !defined(PFNGLCOPYCONVOLUTIONFILTER2DEXTPROC)
typedef void(*PFNGLCOPYCONVOLUTIONFILTER2DEXTPROC)(GLenum,GLenum,GLint,GLint,GLsizei,GLsizei);
#endif
#if !defined(PFNGLCOPYCONVOLUTIONFILTER2DPROC)
typedef void(*PFNGLCOPYCONVOLUTIONFILTER2DPROC)(GLenum,GLenum,GLint,GLint,GLsizei,GLsizei);
#endif
#if !defined(PFNGLCOPYIMAGESUBDATAPROC)
typedef void(*PFNGLCOPYIMAGESUBDATAPROC)(GLuint,GLenum,GLint,GLint,GLint,GLint,GLuint,GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei);
#endif
#if !defined(PFNGLCOPYIMAGESUBDATANVPROC)
typedef void(*PFNGLCOPYIMAGESUBDATANVPROC)(GLuint,GLenum,GLint,GLint,GLint,GLint,GLuint,GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei);
#endif
#if !defined(PFNGLCOPYMULTITEXIMAGE1DEXTPROC)
typedef void(*PFNGLCOPYMULTITEXIMAGE1DEXTPROC)(GLenum,GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLint);
#endif
#if !defined(PFNGLCOPYMULTITEXIMAGE2DEXTPROC)
typedef void(*PFNGLCOPYMULTITEXIMAGE2DEXTPROC)(GLenum,GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLsizei,GLint);
#endif
#if !defined(PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC)
typedef void(*PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC)(GLenum,GLenum,GLint,GLint,GLint,GLint,GLsizei);
#endif
#if !defined(PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC)
typedef void(*PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC)(GLenum,GLenum,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei);
#endif
#if !defined(PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC)
typedef void(*PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC)(GLenum,GLenum,GLint,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei);
#endif
#if !defined(PFNGLCOPYNAMEDBUFFERSUBDATAPROC)
typedef void(*PFNGLCOPYNAMEDBUFFERSUBDATAPROC)(GLuint,GLuint,GLintptr,GLintptr,GLsizeiptr);
#endif
#if !defined(PFNGLCOPYPATHNVPROC)
typedef void(*PFNGLCOPYPATHNVPROC)(GLuint,GLuint);
#endif
#if !defined(PFNGLCOPYPIXELSPROC)
typedef void(*PFNGLCOPYPIXELSPROC)(GLint,GLint,GLsizei,GLsizei,GLenum);
#endif
#if !defined(PFNGLCOPYTEXIMAGE1DEXTPROC)
typedef void(*PFNGLCOPYTEXIMAGE1DEXTPROC)(GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLint);
#endif
#if !defined(PFNGLCOPYTEXIMAGE1DPROC)
typedef void(*PFNGLCOPYTEXIMAGE1DPROC)(GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLint);
#endif
#if !defined(PFNGLCOPYTEXIMAGE2DEXTPROC)
typedef void(*PFNGLCOPYTEXIMAGE2DEXTPROC)(GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLsizei,GLint);
#endif
#if !defined(PFNGLCOPYTEXIMAGE2DPROC)
typedef void(*PFNGLCOPYTEXIMAGE2DPROC)(GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLsizei,GLint);
#endif
#if !defined(PFNGLCOPYTEXSUBIMAGE1DEXTPROC)
typedef void(*PFNGLCOPYTEXSUBIMAGE1DEXTPROC)(GLenum,GLint,GLint,GLint,GLint,GLsizei);
#endif
#if !defined(PFNGLCOPYTEXSUBIMAGE1DPROC)
typedef void(*PFNGLCOPYTEXSUBIMAGE1DPROC)(GLenum,GLint,GLint,GLint,GLint,GLsizei);
#endif
#if !defined(PFNGLCOPYTEXSUBIMAGE2DEXTPROC)
typedef void(*PFNGLCOPYTEXSUBIMAGE2DEXTPROC)(GLenum,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei);
#endif
#if !defined(PFNGLCOPYTEXSUBIMAGE2DPROC)
typedef void(*PFNGLCOPYTEXSUBIMAGE2DPROC)(GLenum,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei);
#endif
#if !defined(PFNGLCOPYTEXSUBIMAGE3DEXTPROC)
typedef void(*PFNGLCOPYTEXSUBIMAGE3DEXTPROC)(GLenum,GLint,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei);
#endif
#if !defined(PFNGLCOPYTEXSUBIMAGE3DPROC)
typedef void(*PFNGLCOPYTEXSUBIMAGE3DPROC)(GLenum,GLint,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei);
#endif
#if !defined(PFNGLCOPYTEXTUREIMAGE1DEXTPROC)
typedef void(*PFNGLCOPYTEXTUREIMAGE1DEXTPROC)(GLuint,GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLint);
#endif
#if !defined(PFNGLCOPYTEXTUREIMAGE2DEXTPROC)
typedef void(*PFNGLCOPYTEXTUREIMAGE2DEXTPROC)(GLuint,GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLsizei,GLint);
#endif
#if !defined(PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC)
typedef void(*PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC)(GLuint,GLenum,GLint,GLint,GLint,GLint,GLsizei);
#endif
#if !defined(PFNGLCOPYTEXTURESUBIMAGE1DPROC)
typedef void(*PFNGLCOPYTEXTURESUBIMAGE1DPROC)(GLuint,GLint,GLint,GLint,GLint,GLsizei);
#endif
#if !defined(PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC)
typedef void(*PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC)(GLuint,GLenum,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei);
#endif
#if !defined(PFNGLCOPYTEXTURESUBIMAGE2DPROC)
typedef void(*PFNGLCOPYTEXTURESUBIMAGE2DPROC)(GLuint,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei);
#endif
#if !defined(PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC)
typedef void(*PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC)(GLuint,GLenum,GLint,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei);
#endif
#if !defined(PFNGLCOPYTEXTURESUBIMAGE3DPROC)
typedef void(*PFNGLCOPYTEXTURESUBIMAGE3DPROC)(GLuint,GLint,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei);
#endif
#if !defined(PFNGLCOVERAGEMODULATIONNVPROC)
typedef void(*PFNGLCOVERAGEMODULATIONNVPROC)(GLenum);
#endif
#if !defined(PFNGLCOVERAGEMODULATIONTABLENVPROC)
typedef void(*PFNGLCOVERAGEMODULATIONTABLENVPROC)(GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLCOVERFILLPATHINSTANCEDNVPROC)
typedef void(*PFNGLCOVERFILLPATHINSTANCEDNVPROC)(GLsizei,GLenum,const void*,GLuint,GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLCOVERFILLPATHNVPROC)
typedef void(*PFNGLCOVERFILLPATHNVPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLCOVERSTROKEPATHINSTANCEDNVPROC)
typedef void(*PFNGLCOVERSTROKEPATHINSTANCEDNVPROC)(GLsizei,GLenum,const void*,GLuint,GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLCOVERSTROKEPATHNVPROC)
typedef void(*PFNGLCOVERSTROKEPATHNVPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLCREATEBUFFERSPROC)
typedef void(*PFNGLCREATEBUFFERSPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLCREATECOMMANDLISTSNVPROC)
typedef void(*PFNGLCREATECOMMANDLISTSNVPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLCREATEFRAMEBUFFERSPROC)
typedef void(*PFNGLCREATEFRAMEBUFFERSPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLCREATEPERFQUERYINTELPROC)
typedef void(*PFNGLCREATEPERFQUERYINTELPROC)(GLuint,GLuint*);
#endif
#if !defined(PFNGLCREATEPROGRAMPIPELINESPROC)
typedef void(*PFNGLCREATEPROGRAMPIPELINESPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLCREATEQUERIESPROC)
typedef void(*PFNGLCREATEQUERIESPROC)(GLenum,GLsizei,GLuint*);
#endif
#if !defined(PFNGLCREATERENDERBUFFERSPROC)
typedef void(*PFNGLCREATERENDERBUFFERSPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLCREATESAMPLERSPROC)
typedef void(*PFNGLCREATESAMPLERSPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLCREATESTATESNVPROC)
typedef void(*PFNGLCREATESTATESNVPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLCREATETEXTURESPROC)
typedef void(*PFNGLCREATETEXTURESPROC)(GLenum,GLsizei,GLuint*);
#endif
#if !defined(PFNGLCREATETRANSFORMFEEDBACKSPROC)
typedef void(*PFNGLCREATETRANSFORMFEEDBACKSPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLCREATEVERTEXARRAYSPROC)
typedef void(*PFNGLCREATEVERTEXARRAYSPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLCULLFACEPROC)
typedef void(*PFNGLCULLFACEPROC)(GLenum);
#endif
#if !defined(PFNGLCULLPARAMETERDVEXTPROC)
typedef void(*PFNGLCULLPARAMETERDVEXTPROC)(GLenum,GLdouble*);
#endif
#if !defined(PFNGLCULLPARAMETERFVEXTPROC)
typedef void(*PFNGLCULLPARAMETERFVEXTPROC)(GLenum,GLfloat*);
#endif
#if !defined(PFNGLCURRENTPALETTEMATRIXARBPROC)
typedef void(*PFNGLCURRENTPALETTEMATRIXARBPROC)(GLint);
#endif
#if !defined(PFNGLDEBUGMESSAGECALLBACKAMDPROC)
typedef void(*PFNGLDEBUGMESSAGECALLBACKAMDPROC)(GLDEBUGPROCAMD,void*);
#endif
#if !defined(PFNGLDEBUGMESSAGECALLBACKARBPROC)
typedef void(*PFNGLDEBUGMESSAGECALLBACKARBPROC)(GLDEBUGPROCARB,const void*);
#endif
#if !defined(PFNGLDEBUGMESSAGECALLBACKPROC)
typedef void(*PFNGLDEBUGMESSAGECALLBACKPROC)(GLDEBUGPROC,const void*);
#endif
#if !defined(PFNGLDEBUGMESSAGECONTROLARBPROC)
typedef void(*PFNGLDEBUGMESSAGECONTROLARBPROC)(GLenum,GLenum,GLenum,GLsizei,const GLuint*,GLboolean);
#endif
#if !defined(PFNGLDEBUGMESSAGECONTROLPROC)
typedef void(*PFNGLDEBUGMESSAGECONTROLPROC)(GLenum,GLenum,GLenum,GLsizei,const GLuint*,GLboolean);
#endif
#if !defined(PFNGLDEBUGMESSAGEENABLEAMDPROC)
typedef void(*PFNGLDEBUGMESSAGEENABLEAMDPROC)(GLenum,GLenum,GLsizei,const GLuint*,GLboolean);
#endif
#if !defined(PFNGLDEBUGMESSAGEINSERTAMDPROC)
typedef void(*PFNGLDEBUGMESSAGEINSERTAMDPROC)(GLenum,GLenum,GLuint,GLsizei,const GLchar*);
#endif
#if !defined(PFNGLDEBUGMESSAGEINSERTARBPROC)
typedef void(*PFNGLDEBUGMESSAGEINSERTARBPROC)(GLenum,GLenum,GLuint,GLenum,GLsizei,const GLchar*);
#endif
#if !defined(PFNGLDEBUGMESSAGEINSERTPROC)
typedef void(*PFNGLDEBUGMESSAGEINSERTPROC)(GLenum,GLenum,GLuint,GLenum,GLsizei,const GLchar*);
#endif
#if !defined(PFNGLDEFORMATIONMAP3DSGIXPROC)
typedef void(*PFNGLDEFORMATIONMAP3DSGIXPROC)(GLenum,GLdouble,GLdouble,GLint,GLint,GLdouble,GLdouble,GLint,GLint,GLdouble,GLdouble,GLint,GLint,const GLdouble*);
#endif
#if !defined(PFNGLDEFORMATIONMAP3FSGIXPROC)
typedef void(*PFNGLDEFORMATIONMAP3FSGIXPROC)(GLenum,GLfloat,GLfloat,GLint,GLint,GLfloat,GLfloat,GLint,GLint,GLfloat,GLfloat,GLint,GLint,const GLfloat*);
#endif
#if !defined(PFNGLDEFORMSGIXPROC)
typedef void(*PFNGLDEFORMSGIXPROC)(GLbitfield);
#endif
#if !defined(PFNGLDELETEASYNCMARKERSSGIXPROC)
typedef void(*PFNGLDELETEASYNCMARKERSSGIXPROC)(GLuint,GLsizei);
#endif
#if !defined(PFNGLDELETEBUFFERSARBPROC)
typedef void(*PFNGLDELETEBUFFERSARBPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETEBUFFERSPROC)
typedef void(*PFNGLDELETEBUFFERSPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETECOMMANDLISTSNVPROC)
typedef void(*PFNGLDELETECOMMANDLISTSNVPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETEFENCESAPPLEPROC)
typedef void(*PFNGLDELETEFENCESAPPLEPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETEFENCESNVPROC)
typedef void(*PFNGLDELETEFENCESNVPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETEFRAGMENTSHADERATIPROC)
typedef void(*PFNGLDELETEFRAGMENTSHADERATIPROC)(GLuint);
#endif
#if !defined(PFNGLDELETEFRAMEBUFFERSEXTPROC)
typedef void(*PFNGLDELETEFRAMEBUFFERSEXTPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETEFRAMEBUFFERSPROC)
typedef void(*PFNGLDELETEFRAMEBUFFERSPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETELISTSPROC)
typedef void(*PFNGLDELETELISTSPROC)(GLuint,GLsizei);
#endif
#if !defined(PFNGLDELETENAMEDSTRINGARBPROC)
typedef void(*PFNGLDELETENAMEDSTRINGARBPROC)(GLint,const GLchar*);
#endif
#if !defined(PFNGLDELETENAMESAMDPROC)
typedef void(*PFNGLDELETENAMESAMDPROC)(GLenum,GLuint,const GLuint*);
#endif
#if !defined(PFNGLDELETEOBJECTARBPROC)
typedef void(*PFNGLDELETEOBJECTARBPROC)(GLhandleARB);
#endif
#if !defined(PFNGLDELETEOCCLUSIONQUERIESNVPROC)
typedef void(*PFNGLDELETEOCCLUSIONQUERIESNVPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETEPATHSNVPROC)
typedef void(*PFNGLDELETEPATHSNVPROC)(GLuint,GLsizei);
#endif
#if !defined(PFNGLDELETEPERFMONITORSAMDPROC)
typedef void(*PFNGLDELETEPERFMONITORSAMDPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLDELETEPERFQUERYINTELPROC)
typedef void(*PFNGLDELETEPERFQUERYINTELPROC)(GLuint);
#endif
#if !defined(PFNGLDELETEPROGRAMPROC)
typedef void(*PFNGLDELETEPROGRAMPROC)(GLuint);
#endif
#if !defined(PFNGLDELETEPROGRAMPIPELINESPROC)
typedef void(*PFNGLDELETEPROGRAMPIPELINESPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETEPROGRAMSARBPROC)
typedef void(*PFNGLDELETEPROGRAMSARBPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETEPROGRAMSNVPROC)
typedef void(*PFNGLDELETEPROGRAMSNVPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETEQUERIESARBPROC)
typedef void(*PFNGLDELETEQUERIESARBPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETEQUERIESPROC)
typedef void(*PFNGLDELETEQUERIESPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETERENDERBUFFERSEXTPROC)
typedef void(*PFNGLDELETERENDERBUFFERSEXTPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETERENDERBUFFERSPROC)
typedef void(*PFNGLDELETERENDERBUFFERSPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETESAMPLERSPROC)
typedef void(*PFNGLDELETESAMPLERSPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETESHADERPROC)
typedef void(*PFNGLDELETESHADERPROC)(GLuint);
#endif
#if !defined(PFNGLDELETESTATESNVPROC)
typedef void(*PFNGLDELETESTATESNVPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETESYNCPROC)
typedef void(*PFNGLDELETESYNCPROC)(GLsync);
#endif
#if !defined(PFNGLDELETETEXTURESEXTPROC)
typedef void(*PFNGLDELETETEXTURESEXTPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETETEXTURESPROC)
typedef void(*PFNGLDELETETEXTURESPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETETRANSFORMFEEDBACKSPROC)
typedef void(*PFNGLDELETETRANSFORMFEEDBACKSPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETETRANSFORMFEEDBACKSNVPROC)
typedef void(*PFNGLDELETETRANSFORMFEEDBACKSNVPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETEVERTEXARRAYSAPPLEPROC)
typedef void(*PFNGLDELETEVERTEXARRAYSAPPLEPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETEVERTEXARRAYSPROC)
typedef void(*PFNGLDELETEVERTEXARRAYSPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLDELETEVERTEXSHADEREXTPROC)
typedef void(*PFNGLDELETEVERTEXSHADEREXTPROC)(GLuint);
#endif
#if !defined(PFNGLDEPTHBOUNDSDNVPROC)
typedef void(*PFNGLDEPTHBOUNDSDNVPROC)(GLdouble,GLdouble);
#endif
#if !defined(PFNGLDEPTHBOUNDSEXTPROC)
typedef void(*PFNGLDEPTHBOUNDSEXTPROC)(GLclampd,GLclampd);
#endif
#if !defined(PFNGLDEPTHFUNCPROC)
typedef void(*PFNGLDEPTHFUNCPROC)(GLenum);
#endif
#if !defined(PFNGLDEPTHMASKPROC)
typedef void(*PFNGLDEPTHMASKPROC)(GLboolean);
#endif
#if !defined(PFNGLDEPTHRANGEARRAYVPROC)
typedef void(*PFNGLDEPTHRANGEARRAYVPROC)(GLuint,GLsizei,const GLdouble*);
#endif
#if !defined(PFNGLDEPTHRANGEDNVPROC)
typedef void(*PFNGLDEPTHRANGEDNVPROC)(GLdouble,GLdouble);
#endif
#if !defined(PFNGLDEPTHRANGEFPROC)
typedef void(*PFNGLDEPTHRANGEFPROC)(GLfloat,GLfloat);
#endif
#if !defined(PFNGLDEPTHRANGEFOESPROC)
typedef void(*PFNGLDEPTHRANGEFOESPROC)(GLclampf,GLclampf);
#endif
#if !defined(PFNGLDEPTHRANGEPROC)
typedef void(*PFNGLDEPTHRANGEPROC)(GLclampd,GLclampd);
#endif
#if !defined(PFNGLDEPTHRANGEINDEXEDPROC)
typedef void(*PFNGLDEPTHRANGEINDEXEDPROC)(GLuint,GLdouble,GLdouble);
#endif
#if !defined(PFNGLDEPTHRANGEXOESPROC)
typedef void(*PFNGLDEPTHRANGEXOESPROC)(GLfixed,GLfixed);
#endif
#if !defined(PFNGLDETACHOBJECTARBPROC)
typedef void(*PFNGLDETACHOBJECTARBPROC)(GLhandleARB,GLhandleARB);
#endif
#if !defined(PFNGLDETACHSHADERPROC)
typedef void(*PFNGLDETACHSHADERPROC)(GLuint,GLuint);
#endif
#if !defined(PFNGLDETAILTEXFUNCSGISPROC)
typedef void(*PFNGLDETAILTEXFUNCSGISPROC)(GLenum,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLDISABLECLIENTSTATEPROC)
typedef void(*PFNGLDISABLECLIENTSTATEPROC)(GLenum);
#endif
#if !defined(PFNGLDISABLECLIENTSTATEIEXTPROC)
typedef void(*PFNGLDISABLECLIENTSTATEIEXTPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC)
typedef void(*PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLDISABLEPROC)
typedef void(*PFNGLDISABLEPROC)(GLenum);
#endif
#if !defined(PFNGLDISABLEIPROC)
typedef void(*PFNGLDISABLEIPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLDISABLEINDEXEDEXTPROC)
typedef void(*PFNGLDISABLEINDEXEDEXTPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLDISABLEVARIANTCLIENTSTATEEXTPROC)
typedef void(*PFNGLDISABLEVARIANTCLIENTSTATEEXTPROC)(GLuint);
#endif
#if !defined(PFNGLDISABLEVERTEXARRAYATTRIBEXTPROC)
typedef void(*PFNGLDISABLEVERTEXARRAYATTRIBEXTPROC)(GLuint,GLuint);
#endif
#if !defined(PFNGLDISABLEVERTEXARRAYATTRIBPROC)
typedef void(*PFNGLDISABLEVERTEXARRAYATTRIBPROC)(GLuint,GLuint);
#endif
#if !defined(PFNGLDISABLEVERTEXARRAYEXTPROC)
typedef void(*PFNGLDISABLEVERTEXARRAYEXTPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLDISABLEVERTEXATTRIBAPPLEPROC)
typedef void(*PFNGLDISABLEVERTEXATTRIBAPPLEPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLDISABLEVERTEXATTRIBARRAYARBPROC)
typedef void(*PFNGLDISABLEVERTEXATTRIBARRAYARBPROC)(GLuint);
#endif
#if !defined(PFNGLDISABLEVERTEXATTRIBARRAYPROC)
typedef void(*PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint);
#endif
#if !defined(PFNGLDISPATCHCOMPUTEPROC)
typedef void(*PFNGLDISPATCHCOMPUTEPROC)(GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLDISPATCHCOMPUTEGROUPSIZEARBPROC)
typedef void(*PFNGLDISPATCHCOMPUTEGROUPSIZEARBPROC)(GLuint,GLuint,GLuint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLDISPATCHCOMPUTEINDIRECTPROC)
typedef void(*PFNGLDISPATCHCOMPUTEINDIRECTPROC)(GLintptr);
#endif
#if !defined(PFNGLDRAWARRAYSEXTPROC)
typedef void(*PFNGLDRAWARRAYSEXTPROC)(GLenum,GLint,GLsizei);
#endif
#if !defined(PFNGLDRAWARRAYSPROC)
typedef void(*PFNGLDRAWARRAYSPROC)(GLenum,GLint,GLsizei);
#endif
#if !defined(PFNGLDRAWARRAYSINDIRECTPROC)
typedef void(*PFNGLDRAWARRAYSINDIRECTPROC)(GLenum,const void*);
#endif
#if !defined(PFNGLDRAWARRAYSINSTANCEDARBPROC)
typedef void(*PFNGLDRAWARRAYSINSTANCEDARBPROC)(GLenum,GLint,GLsizei,GLsizei);
#endif
#if !defined(PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC)
typedef void(*PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC)(GLenum,GLint,GLsizei,GLsizei,GLuint);
#endif
#if !defined(PFNGLDRAWARRAYSINSTANCEDEXTPROC)
typedef void(*PFNGLDRAWARRAYSINSTANCEDEXTPROC)(GLenum,GLint,GLsizei,GLsizei);
#endif
#if !defined(PFNGLDRAWARRAYSINSTANCEDPROC)
typedef void(*PFNGLDRAWARRAYSINSTANCEDPROC)(GLenum,GLint,GLsizei,GLsizei);
#endif
#if !defined(PFNGLDRAWBUFFERPROC)
typedef void(*PFNGLDRAWBUFFERPROC)(GLenum);
#endif
#if !defined(PFNGLDRAWBUFFERSARBPROC)
typedef void(*PFNGLDRAWBUFFERSARBPROC)(GLsizei,const GLenum*);
#endif
#if !defined(PFNGLDRAWBUFFERSATIPROC)
typedef void(*PFNGLDRAWBUFFERSATIPROC)(GLsizei,const GLenum*);
#endif
#if !defined(PFNGLDRAWBUFFERSPROC)
typedef void(*PFNGLDRAWBUFFERSPROC)(GLsizei,const GLenum*);
#endif
#if !defined(PFNGLDRAWCOMMANDSADDRESSNVPROC)
typedef void(*PFNGLDRAWCOMMANDSADDRESSNVPROC)(GLenum,const GLuint64*,const GLsizei*,GLuint);
#endif
#if !defined(PFNGLDRAWCOMMANDSNVPROC)
typedef void(*PFNGLDRAWCOMMANDSNVPROC)(GLenum,GLuint,const GLintptr*,const GLsizei*,GLuint);
#endif
#if !defined(PFNGLDRAWCOMMANDSSTATESADDRESSNVPROC)
typedef void(*PFNGLDRAWCOMMANDSSTATESADDRESSNVPROC)(const GLuint64*,const GLsizei*,const GLuint*,const GLuint*,GLuint);
#endif
#if !defined(PFNGLDRAWCOMMANDSSTATESNVPROC)
typedef void(*PFNGLDRAWCOMMANDSSTATESNVPROC)(GLuint,const GLintptr*,const GLsizei*,const GLuint*,const GLuint*,GLuint);
#endif
#if !defined(PFNGLDRAWELEMENTARRAYAPPLEPROC)
typedef void(*PFNGLDRAWELEMENTARRAYAPPLEPROC)(GLenum,GLint,GLsizei);
#endif
#if !defined(PFNGLDRAWELEMENTARRAYATIPROC)
typedef void(*PFNGLDRAWELEMENTARRAYATIPROC)(GLenum,GLsizei);
#endif
#if !defined(PFNGLDRAWELEMENTSBASEVERTEXPROC)
typedef void(*PFNGLDRAWELEMENTSBASEVERTEXPROC)(GLenum,GLsizei,GLenum,const void*,GLint);
#endif
#if !defined(PFNGLDRAWELEMENTSPROC)
typedef void(*PFNGLDRAWELEMENTSPROC)(GLenum,GLsizei,GLenum,const GLvoid*);
#endif
#if !defined(PFNGLDRAWELEMENTSINDIRECTPROC)
typedef void(*PFNGLDRAWELEMENTSINDIRECTPROC)(GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLDRAWELEMENTSINSTANCEDARBPROC)
typedef void(*PFNGLDRAWELEMENTSINSTANCEDARBPROC)(GLenum,GLsizei,GLenum,const void*,GLsizei);
#endif
#if !defined(PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)
typedef void(*PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)(GLenum,GLsizei,GLenum,const void*,GLsizei,GLuint);
#endif
#if !defined(PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC)
typedef void(*PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC)(GLenum,GLsizei,GLenum,const void*,GLsizei,GLint,GLuint);
#endif
#if !defined(PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)
typedef void(*PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)(GLenum,GLsizei,GLenum,const void*,GLsizei,GLint);
#endif
#if !defined(PFNGLDRAWELEMENTSINSTANCEDEXTPROC)
typedef void(*PFNGLDRAWELEMENTSINSTANCEDEXTPROC)(GLenum,GLsizei,GLenum,const void*,GLsizei);
#endif
#if !defined(PFNGLDRAWELEMENTSINSTANCEDPROC)
typedef void(*PFNGLDRAWELEMENTSINSTANCEDPROC)(GLenum,GLsizei,GLenum,const void*,GLsizei);
#endif
#if !defined(PFNGLDRAWMESHARRAYSSUNPROC)
typedef void(*PFNGLDRAWMESHARRAYSSUNPROC)(GLenum,GLint,GLsizei,GLsizei);
#endif
#if !defined(PFNGLDRAWPIXELSPROC)
typedef void(*PFNGLDRAWPIXELSPROC)(GLsizei,GLsizei,GLenum,GLenum,const GLvoid*);
#endif
#if !defined(PFNGLDRAWRANGEELEMENTARRAYAPPLEPROC)
typedef void(*PFNGLDRAWRANGEELEMENTARRAYAPPLEPROC)(GLenum,GLuint,GLuint,GLint,GLsizei);
#endif
#if !defined(PFNGLDRAWRANGEELEMENTARRAYATIPROC)
typedef void(*PFNGLDRAWRANGEELEMENTARRAYATIPROC)(GLenum,GLuint,GLuint,GLsizei);
#endif
#if !defined(PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)
typedef void(*PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)(GLenum,GLuint,GLuint,GLsizei,GLenum,const void*,GLint);
#endif
#if !defined(PFNGLDRAWRANGEELEMENTSEXTPROC)
typedef void(*PFNGLDRAWRANGEELEMENTSEXTPROC)(GLenum,GLuint,GLuint,GLsizei,GLenum,const void*);
#endif
#if !defined(PFNGLDRAWRANGEELEMENTSPROC)
typedef void(*PFNGLDRAWRANGEELEMENTSPROC)(GLenum,GLuint,GLuint,GLsizei,GLenum,const GLvoid*);
#endif
#if !defined(PFNGLDRAWTEXTURENVPROC)
typedef void(*PFNGLDRAWTEXTURENVPROC)(GLuint,GLuint,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLDRAWTRANSFORMFEEDBACKPROC)
typedef void(*PFNGLDRAWTRANSFORMFEEDBACKPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC)
typedef void(*PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC)(GLenum,GLuint,GLsizei);
#endif
#if !defined(PFNGLDRAWTRANSFORMFEEDBACKNVPROC)
typedef void(*PFNGLDRAWTRANSFORMFEEDBACKNVPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)
typedef void(*PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)(GLenum,GLuint,GLuint);
#endif
#if !defined(PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC)
typedef void(*PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC)(GLenum,GLuint,GLuint,GLsizei);
#endif
#if !defined(PFNGLEDGEFLAGFORMATNVPROC)
typedef void(*PFNGLEDGEFLAGFORMATNVPROC)(GLsizei);
#endif
#if !defined(PFNGLEDGEFLAGPROC)
typedef void(*PFNGLEDGEFLAGPROC)(GLboolean);
#endif
#if !defined(PFNGLEDGEFLAGPOINTEREXTPROC)
typedef void(*PFNGLEDGEFLAGPOINTEREXTPROC)(GLsizei,GLsizei,const GLboolean*);
#endif
#if !defined(PFNGLEDGEFLAGPOINTERPROC)
typedef void(*PFNGLEDGEFLAGPOINTERPROC)(GLsizei,const GLvoid*);
#endif
#if !defined(PFNGLEDGEFLAGPOINTERLISTIBMPROC)
typedef void(*PFNGLEDGEFLAGPOINTERLISTIBMPROC)(GLint,const GLboolean**,GLint);
#endif
#if !defined(PFNGLEDGEFLAGVPROC)
typedef void(*PFNGLEDGEFLAGVPROC)(const GLboolean*);
#endif
#if !defined(PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC)
typedef void(*PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC)(GLenum,GLeglImageOES);
#endif
#if !defined(PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)
typedef void(*PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)(GLenum,GLeglImageOES);
#endif
#if !defined(PFNGLELEMENTPOINTERAPPLEPROC)
typedef void(*PFNGLELEMENTPOINTERAPPLEPROC)(GLenum,const void*);
#endif
#if !defined(PFNGLELEMENTPOINTERATIPROC)
typedef void(*PFNGLELEMENTPOINTERATIPROC)(GLenum,const void*);
#endif
#if !defined(PFNGLENABLECLIENTSTATEPROC)
typedef void(*PFNGLENABLECLIENTSTATEPROC)(GLenum);
#endif
#if !defined(PFNGLENABLECLIENTSTATEIEXTPROC)
typedef void(*PFNGLENABLECLIENTSTATEIEXTPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLENABLECLIENTSTATEINDEXEDEXTPROC)
typedef void(*PFNGLENABLECLIENTSTATEINDEXEDEXTPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLENABLEPROC)
typedef void(*PFNGLENABLEPROC)(GLenum);
#endif
#if !defined(PFNGLENABLEIPROC)
typedef void(*PFNGLENABLEIPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLENABLEINDEXEDEXTPROC)
typedef void(*PFNGLENABLEINDEXEDEXTPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLENABLEVARIANTCLIENTSTATEEXTPROC)
typedef void(*PFNGLENABLEVARIANTCLIENTSTATEEXTPROC)(GLuint);
#endif
#if !defined(PFNGLENABLEVERTEXARRAYATTRIBEXTPROC)
typedef void(*PFNGLENABLEVERTEXARRAYATTRIBEXTPROC)(GLuint,GLuint);
#endif
#if !defined(PFNGLENABLEVERTEXARRAYATTRIBPROC)
typedef void(*PFNGLENABLEVERTEXARRAYATTRIBPROC)(GLuint,GLuint);
#endif
#if !defined(PFNGLENABLEVERTEXARRAYEXTPROC)
typedef void(*PFNGLENABLEVERTEXARRAYEXTPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLENABLEVERTEXATTRIBAPPLEPROC)
typedef void(*PFNGLENABLEVERTEXATTRIBAPPLEPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLENABLEVERTEXATTRIBARRAYARBPROC)
typedef void(*PFNGLENABLEVERTEXATTRIBARRAYARBPROC)(GLuint);
#endif
#if !defined(PFNGLENABLEVERTEXATTRIBARRAYPROC)
typedef void(*PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint);
#endif
#if !defined(PFNGLENDPROC)
typedef void(*PFNGLENDPROC)();
#endif
#if !defined(PFNGLENDCONDITIONALRENDERPROC)
typedef void(*PFNGLENDCONDITIONALRENDERPROC)();
#endif
#if !defined(PFNGLENDCONDITIONALRENDERNVPROC)
typedef void(*PFNGLENDCONDITIONALRENDERNVPROC)();
#endif
#if !defined(PFNGLENDCONDITIONALRENDERNVXPROC)
typedef void(*PFNGLENDCONDITIONALRENDERNVXPROC)();
#endif
#if !defined(PFNGLENDFRAGMENTSHADERATIPROC)
typedef void(*PFNGLENDFRAGMENTSHADERATIPROC)();
#endif
#if !defined(PFNGLENDLISTPROC)
typedef void(*PFNGLENDLISTPROC)();
#endif
#if !defined(PFNGLENDOCCLUSIONQUERYNVPROC)
typedef void(*PFNGLENDOCCLUSIONQUERYNVPROC)();
#endif
#if !defined(PFNGLENDPERFMONITORAMDPROC)
typedef void(*PFNGLENDPERFMONITORAMDPROC)(GLuint);
#endif
#if !defined(PFNGLENDPERFQUERYINTELPROC)
typedef void(*PFNGLENDPERFQUERYINTELPROC)(GLuint);
#endif
#if !defined(PFNGLENDQUERYARBPROC)
typedef void(*PFNGLENDQUERYARBPROC)(GLenum);
#endif
#if !defined(PFNGLENDQUERYPROC)
typedef void(*PFNGLENDQUERYPROC)(GLenum);
#endif
#if !defined(PFNGLENDQUERYINDEXEDPROC)
typedef void(*PFNGLENDQUERYINDEXEDPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLENDTRANSFORMFEEDBACKPROC)
typedef void(*PFNGLENDTRANSFORMFEEDBACKPROC)();
#endif
#if !defined(PFNGLENDTRANSFORMFEEDBACKEXTPROC)
typedef void(*PFNGLENDTRANSFORMFEEDBACKEXTPROC)();
#endif
#if !defined(PFNGLENDTRANSFORMFEEDBACKNVPROC)
typedef void(*PFNGLENDTRANSFORMFEEDBACKNVPROC)();
#endif
#if !defined(PFNGLENDVERTEXSHADEREXTPROC)
typedef void(*PFNGLENDVERTEXSHADEREXTPROC)();
#endif
#if !defined(PFNGLENDVIDEOCAPTURENVPROC)
typedef void(*PFNGLENDVIDEOCAPTURENVPROC)(GLuint);
#endif
#if !defined(PFNGLEVALCOORD1DPROC)
typedef void(*PFNGLEVALCOORD1DPROC)(GLdouble);
#endif
#if !defined(PFNGLEVALCOORD1DVPROC)
typedef void(*PFNGLEVALCOORD1DVPROC)(const GLdouble*);
#endif
#if !defined(PFNGLEVALCOORD1FPROC)
typedef void(*PFNGLEVALCOORD1FPROC)(GLfloat);
#endif
#if !defined(PFNGLEVALCOORD1FVPROC)
typedef void(*PFNGLEVALCOORD1FVPROC)(const GLfloat*);
#endif
#if !defined(PFNGLEVALCOORD1XOESPROC)
typedef void(*PFNGLEVALCOORD1XOESPROC)(GLfixed);
#endif
#if !defined(PFNGLEVALCOORD1XVOESPROC)
typedef void(*PFNGLEVALCOORD1XVOESPROC)(const GLfixed*);
#endif
#if !defined(PFNGLEVALCOORD2DPROC)
typedef void(*PFNGLEVALCOORD2DPROC)(GLdouble,GLdouble);
#endif
#if !defined(PFNGLEVALCOORD2DVPROC)
typedef void(*PFNGLEVALCOORD2DVPROC)(const GLdouble*);
#endif
#if !defined(PFNGLEVALCOORD2FPROC)
typedef void(*PFNGLEVALCOORD2FPROC)(GLfloat,GLfloat);
#endif
#if !defined(PFNGLEVALCOORD2FVPROC)
typedef void(*PFNGLEVALCOORD2FVPROC)(const GLfloat*);
#endif
#if !defined(PFNGLEVALCOORD2XOESPROC)
typedef void(*PFNGLEVALCOORD2XOESPROC)(GLfixed,GLfixed);
#endif
#if !defined(PFNGLEVALCOORD2XVOESPROC)
typedef void(*PFNGLEVALCOORD2XVOESPROC)(const GLfixed*);
#endif
#if !defined(PFNGLEVALMAPSNVPROC)
typedef void(*PFNGLEVALMAPSNVPROC)(GLenum,GLenum);
#endif
#if !defined(PFNGLEVALMESH1PROC)
typedef void(*PFNGLEVALMESH1PROC)(GLenum,GLint,GLint);
#endif
#if !defined(PFNGLEVALMESH2PROC)
typedef void(*PFNGLEVALMESH2PROC)(GLenum,GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLEVALPOINT1PROC)
typedef void(*PFNGLEVALPOINT1PROC)(GLint);
#endif
#if !defined(PFNGLEVALPOINT2PROC)
typedef void(*PFNGLEVALPOINT2PROC)(GLint,GLint);
#endif
#if !defined(PFNGLEVALUATEDEPTHVALUESARBPROC)
typedef void(*PFNGLEVALUATEDEPTHVALUESARBPROC)();
#endif
#if !defined(PFNGLEXECUTEPROGRAMNVPROC)
typedef void(*PFNGLEXECUTEPROGRAMNVPROC)(GLenum,GLuint,const GLfloat*);
#endif
#if !defined(PFNGLEXTRACTCOMPONENTEXTPROC)
typedef void(*PFNGLEXTRACTCOMPONENTEXTPROC)(GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLFEEDBACKBUFFERPROC)
typedef void(*PFNGLFEEDBACKBUFFERPROC)(GLsizei,GLenum,GLfloat*);
#endif
#if !defined(PFNGLFEEDBACKBUFFERXOESPROC)
typedef void(*PFNGLFEEDBACKBUFFERXOESPROC)(GLsizei,GLenum,const GLfixed*);
#endif
#if !defined(PFNGLFINALCOMBINERINPUTNVPROC)
typedef void(*PFNGLFINALCOMBINERINPUTNVPROC)(GLenum,GLenum,GLenum,GLenum);
#endif
#if !defined(PFNGLFINISHPROC)
typedef void(*PFNGLFINISHPROC)();
#endif
#if !defined(PFNGLFINISHFENCEAPPLEPROC)
typedef void(*PFNGLFINISHFENCEAPPLEPROC)(GLuint);
#endif
#if !defined(PFNGLFINISHFENCENVPROC)
typedef void(*PFNGLFINISHFENCENVPROC)(GLuint);
#endif
#if !defined(PFNGLFINISHOBJECTAPPLEPROC)
typedef void(*PFNGLFINISHOBJECTAPPLEPROC)(GLenum,GLint);
#endif
#if !defined(PFNGLFINISHTEXTURESUNXPROC)
typedef void(*PFNGLFINISHTEXTURESUNXPROC)();
#endif
#if !defined(PFNGLFLUSHPROC)
typedef void(*PFNGLFLUSHPROC)();
#endif
#if !defined(PFNGLFLUSHMAPPEDBUFFERRANGEAPPLEPROC)
typedef void(*PFNGLFLUSHMAPPEDBUFFERRANGEAPPLEPROC)(GLenum,GLintptr,GLsizeiptr);
#endif
#if !defined(PFNGLFLUSHMAPPEDBUFFERRANGEPROC)
typedef void(*PFNGLFLUSHMAPPEDBUFFERRANGEPROC)(GLenum,GLintptr,GLsizeiptr);
#endif
#if !defined(PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC)
typedef void(*PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC)(GLuint,GLintptr,GLsizeiptr);
#endif
#if !defined(PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC)
typedef void(*PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC)(GLuint,GLintptr,GLsizeiptr);
#endif
#if !defined(PFNGLFLUSHPIXELDATARANGENVPROC)
typedef void(*PFNGLFLUSHPIXELDATARANGENVPROC)(GLenum);
#endif
#if !defined(PFNGLFLUSHRASTERSGIXPROC)
typedef void(*PFNGLFLUSHRASTERSGIXPROC)();
#endif
#if !defined(PFNGLFLUSHSTATICDATAIBMPROC)
typedef void(*PFNGLFLUSHSTATICDATAIBMPROC)(GLenum);
#endif
#if !defined(PFNGLFLUSHVERTEXARRAYRANGEAPPLEPROC)
typedef void(*PFNGLFLUSHVERTEXARRAYRANGEAPPLEPROC)(GLsizei,void*);
#endif
#if !defined(PFNGLFLUSHVERTEXARRAYRANGENVPROC)
typedef void(*PFNGLFLUSHVERTEXARRAYRANGENVPROC)();
#endif
#if !defined(PFNGLFOGCOORDDEXTPROC)
typedef void(*PFNGLFOGCOORDDEXTPROC)(GLdouble);
#endif
#if !defined(PFNGLFOGCOORDDPROC)
typedef void(*PFNGLFOGCOORDDPROC)(GLdouble);
#endif
#if !defined(PFNGLFOGCOORDDVPROC)
typedef void(*PFNGLFOGCOORDDVPROC)(const GLdouble*);
#endif
#if !defined(PFNGLFOGCOORDDVEXTPROC)
typedef void(*PFNGLFOGCOORDDVEXTPROC)(const GLdouble*);
#endif
#if !defined(PFNGLFOGCOORDFEXTPROC)
typedef void(*PFNGLFOGCOORDFEXTPROC)(GLfloat);
#endif
#if !defined(PFNGLFOGCOORDFPROC)
typedef void(*PFNGLFOGCOORDFPROC)(GLfloat);
#endif
#if !defined(PFNGLFOGCOORDFORMATNVPROC)
typedef void(*PFNGLFOGCOORDFORMATNVPROC)(GLenum,GLsizei);
#endif
#if !defined(PFNGLFOGCOORDFVPROC)
typedef void(*PFNGLFOGCOORDFVPROC)(const GLfloat*);
#endif
#if !defined(PFNGLFOGCOORDFVEXTPROC)
typedef void(*PFNGLFOGCOORDFVEXTPROC)(const GLfloat*);
#endif
#if !defined(PFNGLFOGCOORDHNVPROC)
typedef void(*PFNGLFOGCOORDHNVPROC)(GLhalfNV);
#endif
#if !defined(PFNGLFOGCOORDHVNVPROC)
typedef void(*PFNGLFOGCOORDHVNVPROC)(const GLhalfNV*);
#endif
#if !defined(PFNGLFOGCOORDPOINTEREXTPROC)
typedef void(*PFNGLFOGCOORDPOINTEREXTPROC)(GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLFOGCOORDPOINTERPROC)
typedef void(*PFNGLFOGCOORDPOINTERPROC)(GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLFOGCOORDPOINTERLISTIBMPROC)
typedef void(*PFNGLFOGCOORDPOINTERLISTIBMPROC)(GLenum,GLint,const void**,GLint);
#endif
#if !defined(PFNGLFOGFPROC)
typedef void(*PFNGLFOGFPROC)(GLenum,GLfloat);
#endif
#if !defined(PFNGLFOGFUNCSGISPROC)
typedef void(*PFNGLFOGFUNCSGISPROC)(GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLFOGFVPROC)
typedef void(*PFNGLFOGFVPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLFOGIPROC)
typedef void(*PFNGLFOGIPROC)(GLenum,GLint);
#endif
#if !defined(PFNGLFOGIVPROC)
typedef void(*PFNGLFOGIVPROC)(GLenum,const GLint*);
#endif
#if !defined(PFNGLFOGXOESPROC)
typedef void(*PFNGLFOGXOESPROC)(GLenum,GLfixed);
#endif
#if !defined(PFNGLFOGXVOESPROC)
typedef void(*PFNGLFOGXVOESPROC)(GLenum,const GLfixed*);
#endif
#if !defined(PFNGLFRAGMENTCOLORMATERIALSGIXPROC)
typedef void(*PFNGLFRAGMENTCOLORMATERIALSGIXPROC)(GLenum,GLenum);
#endif
#if !defined(PFNGLFRAGMENTCOVERAGECOLORNVPROC)
typedef void(*PFNGLFRAGMENTCOVERAGECOLORNVPROC)(GLuint);
#endif
#if !defined(PFNGLFRAGMENTLIGHTFSGIXPROC)
typedef void(*PFNGLFRAGMENTLIGHTFSGIXPROC)(GLenum,GLenum,GLfloat);
#endif
#if !defined(PFNGLFRAGMENTLIGHTFVSGIXPROC)
typedef void(*PFNGLFRAGMENTLIGHTFVSGIXPROC)(GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLFRAGMENTLIGHTISGIXPROC)
typedef void(*PFNGLFRAGMENTLIGHTISGIXPROC)(GLenum,GLenum,GLint);
#endif
#if !defined(PFNGLFRAGMENTLIGHTIVSGIXPROC)
typedef void(*PFNGLFRAGMENTLIGHTIVSGIXPROC)(GLenum,GLenum,const GLint*);
#endif
#if !defined(PFNGLFRAGMENTLIGHTMODELFSGIXPROC)
typedef void(*PFNGLFRAGMENTLIGHTMODELFSGIXPROC)(GLenum,GLfloat);
#endif
#if !defined(PFNGLFRAGMENTLIGHTMODELFVSGIXPROC)
typedef void(*PFNGLFRAGMENTLIGHTMODELFVSGIXPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLFRAGMENTLIGHTMODELISGIXPROC)
typedef void(*PFNGLFRAGMENTLIGHTMODELISGIXPROC)(GLenum,GLint);
#endif
#if !defined(PFNGLFRAGMENTLIGHTMODELIVSGIXPROC)
typedef void(*PFNGLFRAGMENTLIGHTMODELIVSGIXPROC)(GLenum,const GLint*);
#endif
#if !defined(PFNGLFRAGMENTMATERIALFSGIXPROC)
typedef void(*PFNGLFRAGMENTMATERIALFSGIXPROC)(GLenum,GLenum,GLfloat);
#endif
#if !defined(PFNGLFRAGMENTMATERIALFVSGIXPROC)
typedef void(*PFNGLFRAGMENTMATERIALFVSGIXPROC)(GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLFRAGMENTMATERIALISGIXPROC)
typedef void(*PFNGLFRAGMENTMATERIALISGIXPROC)(GLenum,GLenum,GLint);
#endif
#if !defined(PFNGLFRAGMENTMATERIALIVSGIXPROC)
typedef void(*PFNGLFRAGMENTMATERIALIVSGIXPROC)(GLenum,GLenum,const GLint*);
#endif
#if !defined(PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC)
typedef void(*PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC)
typedef void(*PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC)(GLuint,GLsizei,const GLenum*);
#endif
#if !defined(PFNGLFRAMEBUFFERPARAMETERIPROC)
typedef void(*PFNGLFRAMEBUFFERPARAMETERIPROC)(GLenum,GLenum,GLint);
#endif
#if !defined(PFNGLFRAMEBUFFERREADBUFFEREXTPROC)
typedef void(*PFNGLFRAMEBUFFERREADBUFFEREXTPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)
typedef void(*PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)(GLenum,GLenum,GLenum,GLuint);
#endif
#if !defined(PFNGLFRAMEBUFFERRENDERBUFFERPROC)
typedef void(*PFNGLFRAMEBUFFERRENDERBUFFERPROC)(GLenum,GLenum,GLenum,GLuint);
#endif
#if !defined(PFNGLFRAMEBUFFERSAMPLELOCATIONSFVARBPROC)
typedef void(*PFNGLFRAMEBUFFERSAMPLELOCATIONSFVARBPROC)(GLenum,GLuint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC)
typedef void(*PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC)(GLenum,GLuint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLFRAMEBUFFERTEXTURE1DEXTPROC)
typedef void(*PFNGLFRAMEBUFFERTEXTURE1DEXTPROC)(GLenum,GLenum,GLenum,GLuint,GLint);
#endif
#if !defined(PFNGLFRAMEBUFFERTEXTURE1DPROC)
typedef void(*PFNGLFRAMEBUFFERTEXTURE1DPROC)(GLenum,GLenum,GLenum,GLuint,GLint);
#endif
#if !defined(PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)
typedef void(*PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)(GLenum,GLenum,GLenum,GLuint,GLint);
#endif
#if !defined(PFNGLFRAMEBUFFERTEXTURE2DPROC)
typedef void(*PFNGLFRAMEBUFFERTEXTURE2DPROC)(GLenum,GLenum,GLenum,GLuint,GLint);
#endif
#if !defined(PFNGLFRAMEBUFFERTEXTURE3DEXTPROC)
typedef void(*PFNGLFRAMEBUFFERTEXTURE3DEXTPROC)(GLenum,GLenum,GLenum,GLuint,GLint,GLint);
#endif
#if !defined(PFNGLFRAMEBUFFERTEXTURE3DPROC)
typedef void(*PFNGLFRAMEBUFFERTEXTURE3DPROC)(GLenum,GLenum,GLenum,GLuint,GLint,GLint);
#endif
#if !defined(PFNGLFRAMEBUFFERTEXTUREARBPROC)
typedef void(*PFNGLFRAMEBUFFERTEXTUREARBPROC)(GLenum,GLenum,GLuint,GLint);
#endif
#if !defined(PFNGLFRAMEBUFFERTEXTUREEXTPROC)
typedef void(*PFNGLFRAMEBUFFERTEXTUREEXTPROC)(GLenum,GLenum,GLuint,GLint);
#endif
#if !defined(PFNGLFRAMEBUFFERTEXTUREFACEARBPROC)
typedef void(*PFNGLFRAMEBUFFERTEXTUREFACEARBPROC)(GLenum,GLenum,GLuint,GLint,GLenum);
#endif
#if !defined(PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC)
typedef void(*PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC)(GLenum,GLenum,GLuint,GLint,GLenum);
#endif
#if !defined(PFNGLFRAMEBUFFERTEXTUREPROC)
typedef void(*PFNGLFRAMEBUFFERTEXTUREPROC)(GLenum,GLenum,GLuint,GLint);
#endif
#if !defined(PFNGLFRAMEBUFFERTEXTURELAYERARBPROC)
typedef void(*PFNGLFRAMEBUFFERTEXTURELAYERARBPROC)(GLenum,GLenum,GLuint,GLint,GLint);
#endif
#if !defined(PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC)
typedef void(*PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC)(GLenum,GLenum,GLuint,GLint,GLint);
#endif
#if !defined(PFNGLFRAMEBUFFERTEXTURELAYERPROC)
typedef void(*PFNGLFRAMEBUFFERTEXTURELAYERPROC)(GLenum,GLenum,GLuint,GLint,GLint);
#endif
#if !defined(PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC)
typedef void(*PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC)(GLenum,GLenum,GLuint,GLint,GLint,GLsizei);
#endif
#if !defined(PFNGLFRAMETERMINATORGREMEDYPROC)
typedef void(*PFNGLFRAMETERMINATORGREMEDYPROC)();
#endif
#if !defined(PFNGLFRAMEZOOMSGIXPROC)
typedef void(*PFNGLFRAMEZOOMSGIXPROC)(GLint);
#endif
#if !defined(PFNGLFREEOBJECTBUFFERATIPROC)
typedef void(*PFNGLFREEOBJECTBUFFERATIPROC)(GLuint);
#endif
#if !defined(PFNGLFRONTFACEPROC)
typedef void(*PFNGLFRONTFACEPROC)(GLenum);
#endif
#if !defined(PFNGLFRUSTUMFOESPROC)
typedef void(*PFNGLFRUSTUMFOESPROC)(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLFRUSTUMPROC)
typedef void(*PFNGLFRUSTUMPROC)(GLdouble,GLdouble,GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLFRUSTUMXOESPROC)
typedef void(*PFNGLFRUSTUMXOESPROC)(GLfixed,GLfixed,GLfixed,GLfixed,GLfixed,GLfixed);
#endif
#if !defined(PFNGLGENBUFFERSARBPROC)
typedef void(*PFNGLGENBUFFERSARBPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLGENBUFFERSPROC)
typedef void(*PFNGLGENBUFFERSPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLGENERATEMIPMAPEXTPROC)
typedef void(*PFNGLGENERATEMIPMAPEXTPROC)(GLenum);
#endif
#if !defined(PFNGLGENERATEMIPMAPPROC)
typedef void(*PFNGLGENERATEMIPMAPPROC)(GLenum);
#endif
#if !defined(PFNGLGENERATEMULTITEXMIPMAPEXTPROC)
typedef void(*PFNGLGENERATEMULTITEXMIPMAPEXTPROC)(GLenum,GLenum);
#endif
#if !defined(PFNGLGENERATETEXTUREMIPMAPEXTPROC)
typedef void(*PFNGLGENERATETEXTUREMIPMAPEXTPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLGENERATETEXTUREMIPMAPPROC)
typedef void(*PFNGLGENERATETEXTUREMIPMAPPROC)(GLuint);
#endif
#if !defined(PFNGLGENFENCESAPPLEPROC)
typedef void(*PFNGLGENFENCESAPPLEPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLGENFENCESNVPROC)
typedef void(*PFNGLGENFENCESNVPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLGENFRAMEBUFFERSEXTPROC)
typedef void(*PFNGLGENFRAMEBUFFERSEXTPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLGENFRAMEBUFFERSPROC)
typedef void(*PFNGLGENFRAMEBUFFERSPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLGENNAMESAMDPROC)
typedef void(*PFNGLGENNAMESAMDPROC)(GLenum,GLuint,GLuint*);
#endif
#if !defined(PFNGLGENOCCLUSIONQUERIESNVPROC)
typedef void(*PFNGLGENOCCLUSIONQUERIESNVPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLGENPERFMONITORSAMDPROC)
typedef void(*PFNGLGENPERFMONITORSAMDPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLGENPROGRAMPIPELINESPROC)
typedef void(*PFNGLGENPROGRAMPIPELINESPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLGENPROGRAMSARBPROC)
typedef void(*PFNGLGENPROGRAMSARBPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLGENPROGRAMSNVPROC)
typedef void(*PFNGLGENPROGRAMSNVPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLGENQUERIESARBPROC)
typedef void(*PFNGLGENQUERIESARBPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLGENQUERIESPROC)
typedef void(*PFNGLGENQUERIESPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLGENRENDERBUFFERSEXTPROC)
typedef void(*PFNGLGENRENDERBUFFERSEXTPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLGENRENDERBUFFERSPROC)
typedef void(*PFNGLGENRENDERBUFFERSPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLGENSAMPLERSPROC)
typedef void(*PFNGLGENSAMPLERSPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLGENTEXTURESEXTPROC)
typedef void(*PFNGLGENTEXTURESEXTPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLGENTEXTURESPROC)
typedef void(*PFNGLGENTEXTURESPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLGENTRANSFORMFEEDBACKSPROC)
typedef void(*PFNGLGENTRANSFORMFEEDBACKSPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLGENTRANSFORMFEEDBACKSNVPROC)
typedef void(*PFNGLGENTRANSFORMFEEDBACKSNVPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLGENVERTEXARRAYSAPPLEPROC)
typedef void(*PFNGLGENVERTEXARRAYSAPPLEPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLGENVERTEXARRAYSPROC)
typedef void(*PFNGLGENVERTEXARRAYSPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC)
typedef void(*PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC)(GLuint,GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETACTIVEATTRIBARBPROC)
typedef void(*PFNGLGETACTIVEATTRIBARBPROC)(GLhandleARB,GLuint,GLsizei,GLsizei*,GLint*,GLenum*,GLcharARB*);
#endif
#if !defined(PFNGLGETACTIVEATTRIBPROC)
typedef void(*PFNGLGETACTIVEATTRIBPROC)(GLuint,GLuint,GLsizei,GLsizei*,GLint*,GLenum*,GLchar*);
#endif
#if !defined(PFNGLGETACTIVESUBROUTINENAMEPROC)
typedef void(*PFNGLGETACTIVESUBROUTINENAMEPROC)(GLuint,GLenum,GLuint,GLsizei,GLsizei*,GLchar*);
#endif
#if !defined(PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)
typedef void(*PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)(GLuint,GLenum,GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)
typedef void(*PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)(GLuint,GLenum,GLuint,GLsizei,GLsizei*,GLchar*);
#endif
#if !defined(PFNGLGETACTIVEUNIFORMARBPROC)
typedef void(*PFNGLGETACTIVEUNIFORMARBPROC)(GLhandleARB,GLuint,GLsizei,GLsizei*,GLint*,GLenum*,GLcharARB*);
#endif
#if !defined(PFNGLGETACTIVEUNIFORMBLOCKIVPROC)
typedef void(*PFNGLGETACTIVEUNIFORMBLOCKIVPROC)(GLuint,GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)
typedef void(*PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)(GLuint,GLuint,GLsizei,GLsizei*,GLchar*);
#endif
#if !defined(PFNGLGETACTIVEUNIFORMPROC)
typedef void(*PFNGLGETACTIVEUNIFORMPROC)(GLuint,GLuint,GLsizei,GLsizei*,GLint*,GLenum*,GLchar*);
#endif
#if !defined(PFNGLGETACTIVEUNIFORMNAMEPROC)
typedef void(*PFNGLGETACTIVEUNIFORMNAMEPROC)(GLuint,GLuint,GLsizei,GLsizei*,GLchar*);
#endif
#if !defined(PFNGLGETACTIVEUNIFORMSIVPROC)
typedef void(*PFNGLGETACTIVEUNIFORMSIVPROC)(GLuint,GLsizei,const GLuint*,GLenum,GLint*);
#endif
#if !defined(PFNGLGETACTIVEVARYINGNVPROC)
typedef void(*PFNGLGETACTIVEVARYINGNVPROC)(GLuint,GLuint,GLsizei,GLsizei*,GLsizei*,GLenum*,GLchar*);
#endif
#if !defined(PFNGLGETARRAYOBJECTFVATIPROC)
typedef void(*PFNGLGETARRAYOBJECTFVATIPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETARRAYOBJECTIVATIPROC)
typedef void(*PFNGLGETARRAYOBJECTIVATIPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETATTACHEDOBJECTSARBPROC)
typedef void(*PFNGLGETATTACHEDOBJECTSARBPROC)(GLhandleARB,GLsizei,GLsizei*,GLhandleARB*);
#endif
#if !defined(PFNGLGETATTACHEDSHADERSPROC)
typedef void(*PFNGLGETATTACHEDSHADERSPROC)(GLuint,GLsizei,GLsizei*,GLuint*);
#endif
#if !defined(PFNGLGETBOOLEANINDEXEDVEXTPROC)
typedef void(*PFNGLGETBOOLEANINDEXEDVEXTPROC)(GLenum,GLuint,GLboolean*);
#endif
#if !defined(PFNGLGETBOOLEANI_VPROC)
typedef void(*PFNGLGETBOOLEANI_VPROC)(GLenum,GLuint,GLboolean*);
#endif
#if !defined(PFNGLGETBOOLEANVPROC)
typedef void(*PFNGLGETBOOLEANVPROC)(GLenum,GLboolean*);
#endif
#if !defined(PFNGLGETBUFFERPARAMETERI64VPROC)
typedef void(*PFNGLGETBUFFERPARAMETERI64VPROC)(GLenum,GLenum,GLint64*);
#endif
#if !defined(PFNGLGETBUFFERPARAMETERIVARBPROC)
typedef void(*PFNGLGETBUFFERPARAMETERIVARBPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETBUFFERPARAMETERIVPROC)
typedef void(*PFNGLGETBUFFERPARAMETERIVPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETBUFFERPARAMETERUI64VNVPROC)
typedef void(*PFNGLGETBUFFERPARAMETERUI64VNVPROC)(GLenum,GLenum,GLuint64EXT*);
#endif
#if !defined(PFNGLGETBUFFERPOINTERVARBPROC)
typedef void(*PFNGLGETBUFFERPOINTERVARBPROC)(GLenum,GLenum,void**);
#endif
#if !defined(PFNGLGETBUFFERPOINTERVPROC)
typedef void(*PFNGLGETBUFFERPOINTERVPROC)(GLenum,GLenum,void**);
#endif
#if !defined(PFNGLGETBUFFERSUBDATAARBPROC)
typedef void(*PFNGLGETBUFFERSUBDATAARBPROC)(GLenum,GLintptrARB,GLsizeiptrARB,void*);
#endif
#if !defined(PFNGLGETBUFFERSUBDATAPROC)
typedef void(*PFNGLGETBUFFERSUBDATAPROC)(GLenum,GLintptr,GLsizeiptr,void*);
#endif
#if !defined(PFNGLGETCLIPPLANEFOESPROC)
typedef void(*PFNGLGETCLIPPLANEFOESPROC)(GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETCLIPPLANEPROC)
typedef void(*PFNGLGETCLIPPLANEPROC)(GLenum,GLdouble*);
#endif
#if !defined(PFNGLGETCLIPPLANEXOESPROC)
typedef void(*PFNGLGETCLIPPLANEXOESPROC)(GLenum,GLfixed*);
#endif
#if !defined(PFNGLGETCOLORTABLEEXTPROC)
typedef void(*PFNGLGETCOLORTABLEEXTPROC)(GLenum,GLenum,GLenum,void*);
#endif
#if !defined(PFNGLGETCOLORTABLEPROC)
typedef void(*PFNGLGETCOLORTABLEPROC)(GLenum,GLenum,GLenum,GLvoid*);
#endif
#if !defined(PFNGLGETCOLORTABLEPARAMETERFVEXTPROC)
typedef void(*PFNGLGETCOLORTABLEPARAMETERFVEXTPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETCOLORTABLEPARAMETERFVPROC)
typedef void(*PFNGLGETCOLORTABLEPARAMETERFVPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETCOLORTABLEPARAMETERFVSGIPROC)
typedef void(*PFNGLGETCOLORTABLEPARAMETERFVSGIPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETCOLORTABLEPARAMETERIVEXTPROC)
typedef void(*PFNGLGETCOLORTABLEPARAMETERIVEXTPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETCOLORTABLEPARAMETERIVPROC)
typedef void(*PFNGLGETCOLORTABLEPARAMETERIVPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETCOLORTABLEPARAMETERIVSGIPROC)
typedef void(*PFNGLGETCOLORTABLEPARAMETERIVSGIPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETCOLORTABLESGIPROC)
typedef void(*PFNGLGETCOLORTABLESGIPROC)(GLenum,GLenum,GLenum,void*);
#endif
#if !defined(PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC)
typedef void(*PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC)(GLenum,GLenum,GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC)
typedef void(*PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC)(GLenum,GLenum,GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC)
typedef void(*PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC)(GLenum,GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC)
typedef void(*PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC)(GLenum,GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETCOMBINERSTAGEPARAMETERFVNVPROC)
typedef void(*PFNGLGETCOMBINERSTAGEPARAMETERFVNVPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC)
typedef void(*PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC)(GLenum,GLenum,GLint,void*);
#endif
#if !defined(PFNGLGETCOMPRESSEDTEXIMAGEARBPROC)
typedef void(*PFNGLGETCOMPRESSEDTEXIMAGEARBPROC)(GLenum,GLint,void*);
#endif
#if !defined(PFNGLGETCOMPRESSEDTEXIMAGEPROC)
typedef void(*PFNGLGETCOMPRESSEDTEXIMAGEPROC)(GLenum,GLint,GLvoid*);
#endif
#if !defined(PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC)
typedef void(*PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC)(GLuint,GLenum,GLint,void*);
#endif
#if !defined(PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC)
typedef void(*PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC)(GLuint,GLint,GLsizei,void*);
#endif
#if !defined(PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC)
typedef void(*PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC)(GLuint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLsizei,void*);
#endif
#if !defined(PFNGLGETCONVOLUTIONFILTEREXTPROC)
typedef void(*PFNGLGETCONVOLUTIONFILTEREXTPROC)(GLenum,GLenum,GLenum,void*);
#endif
#if !defined(PFNGLGETCONVOLUTIONFILTERPROC)
typedef void(*PFNGLGETCONVOLUTIONFILTERPROC)(GLenum,GLenum,GLenum,GLvoid*);
#endif
#if !defined(PFNGLGETCONVOLUTIONPARAMETERFVEXTPROC)
typedef void(*PFNGLGETCONVOLUTIONPARAMETERFVEXTPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETCONVOLUTIONPARAMETERFVPROC)
typedef void(*PFNGLGETCONVOLUTIONPARAMETERFVPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETCONVOLUTIONPARAMETERIVEXTPROC)
typedef void(*PFNGLGETCONVOLUTIONPARAMETERIVEXTPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETCONVOLUTIONPARAMETERIVPROC)
typedef void(*PFNGLGETCONVOLUTIONPARAMETERIVPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETCONVOLUTIONPARAMETERXVOESPROC)
typedef void(*PFNGLGETCONVOLUTIONPARAMETERXVOESPROC)(GLenum,GLenum,GLfixed*);
#endif
#if !defined(PFNGLGETCOVERAGEMODULATIONTABLENVPROC)
typedef void(*PFNGLGETCOVERAGEMODULATIONTABLENVPROC)(GLsizei,GLfloat*);
#endif
#if !defined(PFNGLGETDETAILTEXFUNCSGISPROC)
typedef void(*PFNGLGETDETAILTEXFUNCSGISPROC)(GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETDOUBLEINDEXEDVEXTPROC)
typedef void(*PFNGLGETDOUBLEINDEXEDVEXTPROC)(GLenum,GLuint,GLdouble*);
#endif
#if !defined(PFNGLGETDOUBLEI_VEXTPROC)
typedef void(*PFNGLGETDOUBLEI_VEXTPROC)(GLenum,GLuint,GLdouble*);
#endif
#if !defined(PFNGLGETDOUBLEI_VPROC)
typedef void(*PFNGLGETDOUBLEI_VPROC)(GLenum,GLuint,GLdouble*);
#endif
#if !defined(PFNGLGETDOUBLEVPROC)
typedef void(*PFNGLGETDOUBLEVPROC)(GLenum,GLdouble*);
#endif
#if !defined(PFNGLGETFENCEIVNVPROC)
typedef void(*PFNGLGETFENCEIVNVPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC)
typedef void(*PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC)
typedef void(*PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETFIRSTPERFQUERYIDINTELPROC)
typedef void(*PFNGLGETFIRSTPERFQUERYIDINTELPROC)(GLuint*);
#endif
#if !defined(PFNGLGETFIXEDVOESPROC)
typedef void(*PFNGLGETFIXEDVOESPROC)(GLenum,GLfixed*);
#endif
#if !defined(PFNGLGETFLOATINDEXEDVEXTPROC)
typedef void(*PFNGLGETFLOATINDEXEDVEXTPROC)(GLenum,GLuint,GLfloat*);
#endif
#if !defined(PFNGLGETFLOATI_VEXTPROC)
typedef void(*PFNGLGETFLOATI_VEXTPROC)(GLenum,GLuint,GLfloat*);
#endif
#if !defined(PFNGLGETFLOATI_VPROC)
typedef void(*PFNGLGETFLOATI_VPROC)(GLenum,GLuint,GLfloat*);
#endif
#if !defined(PFNGLGETFLOATVPROC)
typedef void(*PFNGLGETFLOATVPROC)(GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETFOGFUNCSGISPROC)
typedef void(*PFNGLGETFOGFUNCSGISPROC)(GLfloat*);
#endif
#if !defined(PFNGLGETFRAGMENTLIGHTFVSGIXPROC)
typedef void(*PFNGLGETFRAGMENTLIGHTFVSGIXPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETFRAGMENTLIGHTIVSGIXPROC)
typedef void(*PFNGLGETFRAGMENTLIGHTIVSGIXPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETFRAGMENTMATERIALFVSGIXPROC)
typedef void(*PFNGLGETFRAGMENTMATERIALFVSGIXPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETFRAGMENTMATERIALIVSGIXPROC)
typedef void(*PFNGLGETFRAGMENTMATERIALIVSGIXPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC)
typedef void(*PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC)(GLenum,GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)
typedef void(*PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLenum,GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC)
typedef void(*PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETFRAMEBUFFERPARAMETERIVPROC)
typedef void(*PFNGLGETFRAMEBUFFERPARAMETERIVPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETHISTOGRAMEXTPROC)
typedef void(*PFNGLGETHISTOGRAMEXTPROC)(GLenum,GLboolean,GLenum,GLenum,void*);
#endif
#if !defined(PFNGLGETHISTOGRAMPROC)
typedef void(*PFNGLGETHISTOGRAMPROC)(GLenum,GLboolean,GLenum,GLenum,GLvoid*);
#endif
#if !defined(PFNGLGETHISTOGRAMPARAMETERFVEXTPROC)
typedef void(*PFNGLGETHISTOGRAMPARAMETERFVEXTPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETHISTOGRAMPARAMETERFVPROC)
typedef void(*PFNGLGETHISTOGRAMPARAMETERFVPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETHISTOGRAMPARAMETERIVEXTPROC)
typedef void(*PFNGLGETHISTOGRAMPARAMETERIVEXTPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETHISTOGRAMPARAMETERIVPROC)
typedef void(*PFNGLGETHISTOGRAMPARAMETERIVPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETHISTOGRAMPARAMETERXVOESPROC)
typedef void(*PFNGLGETHISTOGRAMPARAMETERXVOESPROC)(GLenum,GLenum,GLfixed*);
#endif
#if !defined(PFNGLGETIMAGETRANSFORMPARAMETERFVHPPROC)
typedef void(*PFNGLGETIMAGETRANSFORMPARAMETERFVHPPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETIMAGETRANSFORMPARAMETERIVHPPROC)
typedef void(*PFNGLGETIMAGETRANSFORMPARAMETERIVHPPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETINFOLOGARBPROC)
typedef void(*PFNGLGETINFOLOGARBPROC)(GLhandleARB,GLsizei,GLsizei*,GLcharARB*);
#endif
#if !defined(PFNGLGETINTEGER64I_VPROC)
typedef void(*PFNGLGETINTEGER64I_VPROC)(GLenum,GLuint,GLint64*);
#endif
#if !defined(PFNGLGETINTEGER64VPROC)
typedef void(*PFNGLGETINTEGER64VPROC)(GLenum,GLint64*);
#endif
#if !defined(PFNGLGETINTEGERINDEXEDVEXTPROC)
typedef void(*PFNGLGETINTEGERINDEXEDVEXTPROC)(GLenum,GLuint,GLint*);
#endif
#if !defined(PFNGLGETINTEGERI_VPROC)
typedef void(*PFNGLGETINTEGERI_VPROC)(GLenum,GLuint,GLint*);
#endif
#if !defined(PFNGLGETINTEGERUI64I_VNVPROC)
typedef void(*PFNGLGETINTEGERUI64I_VNVPROC)(GLenum,GLuint,GLuint64EXT*);
#endif
#if !defined(PFNGLGETINTEGERUI64VNVPROC)
typedef void(*PFNGLGETINTEGERUI64VNVPROC)(GLenum,GLuint64EXT*);
#endif
#if !defined(PFNGLGETINTEGERVPROC)
typedef void(*PFNGLGETINTEGERVPROC)(GLenum,GLint*);
#endif
#if !defined(PFNGLGETINTERNALFORMATI64VPROC)
typedef void(*PFNGLGETINTERNALFORMATI64VPROC)(GLenum,GLenum,GLenum,GLsizei,GLint64*);
#endif
#if !defined(PFNGLGETINTERNALFORMATIVPROC)
typedef void(*PFNGLGETINTERNALFORMATIVPROC)(GLenum,GLenum,GLenum,GLsizei,GLint*);
#endif
#if !defined(PFNGLGETINTERNALFORMATSAMPLEIVNVPROC)
typedef void(*PFNGLGETINTERNALFORMATSAMPLEIVNVPROC)(GLenum,GLenum,GLsizei,GLenum,GLsizei,GLint*);
#endif
#if !defined(PFNGLGETINVARIANTBOOLEANVEXTPROC)
typedef void(*PFNGLGETINVARIANTBOOLEANVEXTPROC)(GLuint,GLenum,GLboolean*);
#endif
#if !defined(PFNGLGETINVARIANTFLOATVEXTPROC)
typedef void(*PFNGLGETINVARIANTFLOATVEXTPROC)(GLuint,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETINVARIANTINTEGERVEXTPROC)
typedef void(*PFNGLGETINVARIANTINTEGERVEXTPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETLIGHTFVPROC)
typedef void(*PFNGLGETLIGHTFVPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETLIGHTIVPROC)
typedef void(*PFNGLGETLIGHTIVPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETLIGHTXOESPROC)
typedef void(*PFNGLGETLIGHTXOESPROC)(GLenum,GLenum,GLfixed*);
#endif
#if !defined(PFNGLGETLISTPARAMETERFVSGIXPROC)
typedef void(*PFNGLGETLISTPARAMETERFVSGIXPROC)(GLuint,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETLISTPARAMETERIVSGIXPROC)
typedef void(*PFNGLGETLISTPARAMETERIVSGIXPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETLOCALCONSTANTBOOLEANVEXTPROC)
typedef void(*PFNGLGETLOCALCONSTANTBOOLEANVEXTPROC)(GLuint,GLenum,GLboolean*);
#endif
#if !defined(PFNGLGETLOCALCONSTANTFLOATVEXTPROC)
typedef void(*PFNGLGETLOCALCONSTANTFLOATVEXTPROC)(GLuint,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETLOCALCONSTANTINTEGERVEXTPROC)
typedef void(*PFNGLGETLOCALCONSTANTINTEGERVEXTPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETMAPATTRIBPARAMETERFVNVPROC)
typedef void(*PFNGLGETMAPATTRIBPARAMETERFVNVPROC)(GLenum,GLuint,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETMAPATTRIBPARAMETERIVNVPROC)
typedef void(*PFNGLGETMAPATTRIBPARAMETERIVNVPROC)(GLenum,GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETMAPCONTROLPOINTSNVPROC)
typedef void(*PFNGLGETMAPCONTROLPOINTSNVPROC)(GLenum,GLuint,GLenum,GLsizei,GLsizei,GLboolean,void*);
#endif
#if !defined(PFNGLGETMAPDVPROC)
typedef void(*PFNGLGETMAPDVPROC)(GLenum,GLenum,GLdouble*);
#endif
#if !defined(PFNGLGETMAPFVPROC)
typedef void(*PFNGLGETMAPFVPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETMAPIVPROC)
typedef void(*PFNGLGETMAPIVPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETMAPPARAMETERFVNVPROC)
typedef void(*PFNGLGETMAPPARAMETERFVNVPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETMAPPARAMETERIVNVPROC)
typedef void(*PFNGLGETMAPPARAMETERIVNVPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETMAPXVOESPROC)
typedef void(*PFNGLGETMAPXVOESPROC)(GLenum,GLenum,GLfixed*);
#endif
#if !defined(PFNGLGETMATERIALFVPROC)
typedef void(*PFNGLGETMATERIALFVPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETMATERIALIVPROC)
typedef void(*PFNGLGETMATERIALIVPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETMATERIALXOESPROC)
typedef void(*PFNGLGETMATERIALXOESPROC)(GLenum,GLenum,GLfixed);
#endif
#if !defined(PFNGLGETMINMAXEXTPROC)
typedef void(*PFNGLGETMINMAXEXTPROC)(GLenum,GLboolean,GLenum,GLenum,void*);
#endif
#if !defined(PFNGLGETMINMAXPROC)
typedef void(*PFNGLGETMINMAXPROC)(GLenum,GLboolean,GLenum,GLenum,GLvoid*);
#endif
#if !defined(PFNGLGETMINMAXPARAMETERFVEXTPROC)
typedef void(*PFNGLGETMINMAXPARAMETERFVEXTPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETMINMAXPARAMETERFVPROC)
typedef void(*PFNGLGETMINMAXPARAMETERFVPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETMINMAXPARAMETERIVEXTPROC)
typedef void(*PFNGLGETMINMAXPARAMETERIVEXTPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETMINMAXPARAMETERIVPROC)
typedef void(*PFNGLGETMINMAXPARAMETERIVPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETMULTISAMPLEFVPROC)
typedef void(*PFNGLGETMULTISAMPLEFVPROC)(GLenum,GLuint,GLfloat*);
#endif
#if !defined(PFNGLGETMULTISAMPLEFVNVPROC)
typedef void(*PFNGLGETMULTISAMPLEFVNVPROC)(GLenum,GLuint,GLfloat*);
#endif
#if !defined(PFNGLGETMULTITEXENVFVEXTPROC)
typedef void(*PFNGLGETMULTITEXENVFVEXTPROC)(GLenum,GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETMULTITEXENVIVEXTPROC)
typedef void(*PFNGLGETMULTITEXENVIVEXTPROC)(GLenum,GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETMULTITEXGENDVEXTPROC)
typedef void(*PFNGLGETMULTITEXGENDVEXTPROC)(GLenum,GLenum,GLenum,GLdouble*);
#endif
#if !defined(PFNGLGETMULTITEXGENFVEXTPROC)
typedef void(*PFNGLGETMULTITEXGENFVEXTPROC)(GLenum,GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETMULTITEXGENIVEXTPROC)
typedef void(*PFNGLGETMULTITEXGENIVEXTPROC)(GLenum,GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETMULTITEXIMAGEEXTPROC)
typedef void(*PFNGLGETMULTITEXIMAGEEXTPROC)(GLenum,GLenum,GLint,GLenum,GLenum,void*);
#endif
#if !defined(PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC)
typedef void(*PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC)(GLenum,GLenum,GLint,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC)
typedef void(*PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC)(GLenum,GLenum,GLint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETMULTITEXPARAMETERFVEXTPROC)
typedef void(*PFNGLGETMULTITEXPARAMETERFVEXTPROC)(GLenum,GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETMULTITEXPARAMETERIIVEXTPROC)
typedef void(*PFNGLGETMULTITEXPARAMETERIIVEXTPROC)(GLenum,GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETMULTITEXPARAMETERIUIVEXTPROC)
typedef void(*PFNGLGETMULTITEXPARAMETERIUIVEXTPROC)(GLenum,GLenum,GLenum,GLuint*);
#endif
#if !defined(PFNGLGETMULTITEXPARAMETERIVEXTPROC)
typedef void(*PFNGLGETMULTITEXPARAMETERIVEXTPROC)(GLenum,GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETNAMEDBUFFERPARAMETERI64VPROC)
typedef void(*PFNGLGETNAMEDBUFFERPARAMETERI64VPROC)(GLuint,GLenum,GLint64*);
#endif
#if !defined(PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC)
typedef void(*PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETNAMEDBUFFERPARAMETERIVPROC)
typedef void(*PFNGLGETNAMEDBUFFERPARAMETERIVPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETNAMEDBUFFERPARAMETERUI64VNVPROC)
typedef void(*PFNGLGETNAMEDBUFFERPARAMETERUI64VNVPROC)(GLuint,GLenum,GLuint64EXT*);
#endif
#if !defined(PFNGLGETNAMEDBUFFERPOINTERVEXTPROC)
typedef void(*PFNGLGETNAMEDBUFFERPOINTERVEXTPROC)(GLuint,GLenum,void**);
#endif
#if !defined(PFNGLGETNAMEDBUFFERPOINTERVPROC)
typedef void(*PFNGLGETNAMEDBUFFERPOINTERVPROC)(GLuint,GLenum,void**);
#endif
#if !defined(PFNGLGETNAMEDBUFFERSUBDATAEXTPROC)
typedef void(*PFNGLGETNAMEDBUFFERSUBDATAEXTPROC)(GLuint,GLintptr,GLsizeiptr,void*);
#endif
#if !defined(PFNGLGETNAMEDBUFFERSUBDATAPROC)
typedef void(*PFNGLGETNAMEDBUFFERSUBDATAPROC)(GLuint,GLintptr,GLsizeiptr,void*);
#endif
#if !defined(PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC)
typedef void(*PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC)(GLuint,GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC)
typedef void(*PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLuint,GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVEXTPROC)
typedef void(*PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVEXTPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC)
typedef void(*PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETNAMEDPROGRAMIVEXTPROC)
typedef void(*PFNGLGETNAMEDPROGRAMIVEXTPROC)(GLuint,GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC)
typedef void(*PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC)(GLuint,GLenum,GLuint,GLdouble*);
#endif
#if !defined(PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC)
typedef void(*PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC)(GLuint,GLenum,GLuint,GLfloat*);
#endif
#if !defined(PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC)
typedef void(*PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC)(GLuint,GLenum,GLuint,GLint*);
#endif
#if !defined(PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC)
typedef void(*PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC)(GLuint,GLenum,GLuint,GLuint*);
#endif
#if !defined(PFNGLGETNAMEDPROGRAMSTRINGEXTPROC)
typedef void(*PFNGLGETNAMEDPROGRAMSTRINGEXTPROC)(GLuint,GLenum,GLenum,void*);
#endif
#if !defined(PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC)
typedef void(*PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC)
typedef void(*PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETNAMEDSTRINGARBPROC)
typedef void(*PFNGLGETNAMEDSTRINGARBPROC)(GLint,const GLchar*,GLsizei,GLint*,GLchar*);
#endif
#if !defined(PFNGLGETNAMEDSTRINGIVARBPROC)
typedef void(*PFNGLGETNAMEDSTRINGIVARBPROC)(GLint,const GLchar*,GLenum,GLint*);
#endif
#if !defined(PFNGLGETNCOLORTABLEARBPROC)
typedef void(*PFNGLGETNCOLORTABLEARBPROC)(GLenum,GLenum,GLenum,GLsizei,void*);
#endif
#if !defined(PFNGLGETNCOLORTABLEPROC)
typedef void(*PFNGLGETNCOLORTABLEPROC)(GLenum,GLenum,GLenum,GLsizei,void*);
#endif
#if !defined(PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC)
typedef void(*PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC)(GLenum,GLint,GLsizei,void*);
#endif
#if !defined(PFNGLGETNCOMPRESSEDTEXIMAGEPROC)
typedef void(*PFNGLGETNCOMPRESSEDTEXIMAGEPROC)(GLenum,GLint,GLsizei,void*);
#endif
#if !defined(PFNGLGETNCONVOLUTIONFILTERARBPROC)
typedef void(*PFNGLGETNCONVOLUTIONFILTERARBPROC)(GLenum,GLenum,GLenum,GLsizei,void*);
#endif
#if !defined(PFNGLGETNCONVOLUTIONFILTERPROC)
typedef void(*PFNGLGETNCONVOLUTIONFILTERPROC)(GLenum,GLenum,GLenum,GLsizei,void*);
#endif
#if !defined(PFNGLGETNEXTPERFQUERYIDINTELPROC)
typedef void(*PFNGLGETNEXTPERFQUERYIDINTELPROC)(GLuint,GLuint*);
#endif
#if !defined(PFNGLGETNHISTOGRAMARBPROC)
typedef void(*PFNGLGETNHISTOGRAMARBPROC)(GLenum,GLboolean,GLenum,GLenum,GLsizei,void*);
#endif
#if !defined(PFNGLGETNHISTOGRAMPROC)
typedef void(*PFNGLGETNHISTOGRAMPROC)(GLenum,GLboolean,GLenum,GLenum,GLsizei,void*);
#endif
#if !defined(PFNGLGETNMAPDVARBPROC)
typedef void(*PFNGLGETNMAPDVARBPROC)(GLenum,GLenum,GLsizei,GLdouble*);
#endif
#if !defined(PFNGLGETNMAPDVPROC)
typedef void(*PFNGLGETNMAPDVPROC)(GLenum,GLenum,GLsizei,GLdouble*);
#endif
#if !defined(PFNGLGETNMAPFVARBPROC)
typedef void(*PFNGLGETNMAPFVARBPROC)(GLenum,GLenum,GLsizei,GLfloat*);
#endif
#if !defined(PFNGLGETNMAPFVPROC)
typedef void(*PFNGLGETNMAPFVPROC)(GLenum,GLenum,GLsizei,GLfloat*);
#endif
#if !defined(PFNGLGETNMAPIVARBPROC)
typedef void(*PFNGLGETNMAPIVARBPROC)(GLenum,GLenum,GLsizei,GLint*);
#endif
#if !defined(PFNGLGETNMAPIVPROC)
typedef void(*PFNGLGETNMAPIVPROC)(GLenum,GLenum,GLsizei,GLint*);
#endif
#if !defined(PFNGLGETNMINMAXARBPROC)
typedef void(*PFNGLGETNMINMAXARBPROC)(GLenum,GLboolean,GLenum,GLenum,GLsizei,void*);
#endif
#if !defined(PFNGLGETNMINMAXPROC)
typedef void(*PFNGLGETNMINMAXPROC)(GLenum,GLboolean,GLenum,GLenum,GLsizei,void*);
#endif
#if !defined(PFNGLGETNPIXELMAPFVARBPROC)
typedef void(*PFNGLGETNPIXELMAPFVARBPROC)(GLenum,GLsizei,GLfloat*);
#endif
#if !defined(PFNGLGETNPIXELMAPFVPROC)
typedef void(*PFNGLGETNPIXELMAPFVPROC)(GLenum,GLsizei,GLfloat*);
#endif
#if !defined(PFNGLGETNPIXELMAPUIVARBPROC)
typedef void(*PFNGLGETNPIXELMAPUIVARBPROC)(GLenum,GLsizei,GLuint*);
#endif
#if !defined(PFNGLGETNPIXELMAPUIVPROC)
typedef void(*PFNGLGETNPIXELMAPUIVPROC)(GLenum,GLsizei,GLuint*);
#endif
#if !defined(PFNGLGETNPIXELMAPUSVARBPROC)
typedef void(*PFNGLGETNPIXELMAPUSVARBPROC)(GLenum,GLsizei,GLushort*);
#endif
#if !defined(PFNGLGETNPIXELMAPUSVPROC)
typedef void(*PFNGLGETNPIXELMAPUSVPROC)(GLenum,GLsizei,GLushort*);
#endif
#if !defined(PFNGLGETNPOLYGONSTIPPLEARBPROC)
typedef void(*PFNGLGETNPOLYGONSTIPPLEARBPROC)(GLsizei,GLubyte*);
#endif
#if !defined(PFNGLGETNPOLYGONSTIPPLEPROC)
typedef void(*PFNGLGETNPOLYGONSTIPPLEPROC)(GLsizei,GLubyte*);
#endif
#if !defined(PFNGLGETNSEPARABLEFILTERARBPROC)
typedef void(*PFNGLGETNSEPARABLEFILTERARBPROC)(GLenum,GLenum,GLenum,GLsizei,void*,GLsizei,void*,void*);
#endif
#if !defined(PFNGLGETNSEPARABLEFILTERPROC)
typedef void(*PFNGLGETNSEPARABLEFILTERPROC)(GLenum,GLenum,GLenum,GLsizei,void*,GLsizei,void*,void*);
#endif
#if !defined(PFNGLGETNTEXIMAGEARBPROC)
typedef void(*PFNGLGETNTEXIMAGEARBPROC)(GLenum,GLint,GLenum,GLenum,GLsizei,void*);
#endif
#if !defined(PFNGLGETNTEXIMAGEPROC)
typedef void(*PFNGLGETNTEXIMAGEPROC)(GLenum,GLint,GLenum,GLenum,GLsizei,void*);
#endif
#if !defined(PFNGLGETNUNIFORMDVARBPROC)
typedef void(*PFNGLGETNUNIFORMDVARBPROC)(GLuint,GLint,GLsizei,GLdouble*);
#endif
#if !defined(PFNGLGETNUNIFORMDVPROC)
typedef void(*PFNGLGETNUNIFORMDVPROC)(GLuint,GLint,GLsizei,GLdouble*);
#endif
#if !defined(PFNGLGETNUNIFORMFVARBPROC)
typedef void(*PFNGLGETNUNIFORMFVARBPROC)(GLuint,GLint,GLsizei,GLfloat*);
#endif
#if !defined(PFNGLGETNUNIFORMFVPROC)
typedef void(*PFNGLGETNUNIFORMFVPROC)(GLuint,GLint,GLsizei,GLfloat*);
#endif
#if !defined(PFNGLGETNUNIFORMI64VARBPROC)
typedef void(*PFNGLGETNUNIFORMI64VARBPROC)(GLuint,GLint,GLsizei,GLint64*);
#endif
#if !defined(PFNGLGETNUNIFORMIVARBPROC)
typedef void(*PFNGLGETNUNIFORMIVARBPROC)(GLuint,GLint,GLsizei,GLint*);
#endif
#if !defined(PFNGLGETNUNIFORMIVPROC)
typedef void(*PFNGLGETNUNIFORMIVPROC)(GLuint,GLint,GLsizei,GLint*);
#endif
#if !defined(PFNGLGETNUNIFORMUI64VARBPROC)
typedef void(*PFNGLGETNUNIFORMUI64VARBPROC)(GLuint,GLint,GLsizei,GLuint64*);
#endif
#if !defined(PFNGLGETNUNIFORMUIVARBPROC)
typedef void(*PFNGLGETNUNIFORMUIVARBPROC)(GLuint,GLint,GLsizei,GLuint*);
#endif
#if !defined(PFNGLGETNUNIFORMUIVPROC)
typedef void(*PFNGLGETNUNIFORMUIVPROC)(GLuint,GLint,GLsizei,GLuint*);
#endif
#if !defined(PFNGLGETOBJECTBUFFERFVATIPROC)
typedef void(*PFNGLGETOBJECTBUFFERFVATIPROC)(GLuint,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETOBJECTBUFFERIVATIPROC)
typedef void(*PFNGLGETOBJECTBUFFERIVATIPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETOBJECTLABELEXTPROC)
typedef void(*PFNGLGETOBJECTLABELEXTPROC)(GLenum,GLuint,GLsizei,GLsizei*,GLchar*);
#endif
#if !defined(PFNGLGETOBJECTLABELPROC)
typedef void(*PFNGLGETOBJECTLABELPROC)(GLenum,GLuint,GLsizei,GLsizei*,GLchar*);
#endif
#if !defined(PFNGLGETOBJECTPARAMETERFVARBPROC)
typedef void(*PFNGLGETOBJECTPARAMETERFVARBPROC)(GLhandleARB,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETOBJECTPARAMETERIVAPPLEPROC)
typedef void(*PFNGLGETOBJECTPARAMETERIVAPPLEPROC)(GLenum,GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETOBJECTPARAMETERIVARBPROC)
typedef void(*PFNGLGETOBJECTPARAMETERIVARBPROC)(GLhandleARB,GLenum,GLint*);
#endif
#if !defined(PFNGLGETOBJECTPTRLABELPROC)
typedef void(*PFNGLGETOBJECTPTRLABELPROC)(const void*,GLsizei,GLsizei*,GLchar*);
#endif
#if !defined(PFNGLGETOCCLUSIONQUERYIVNVPROC)
typedef void(*PFNGLGETOCCLUSIONQUERYIVNVPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETOCCLUSIONQUERYUIVNVPROC)
typedef void(*PFNGLGETOCCLUSIONQUERYUIVNVPROC)(GLuint,GLenum,GLuint*);
#endif
#if !defined(PFNGLGETPATHCOLORGENFVNVPROC)
typedef void(*PFNGLGETPATHCOLORGENFVNVPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETPATHCOLORGENIVNVPROC)
typedef void(*PFNGLGETPATHCOLORGENIVNVPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETPATHCOMMANDSNVPROC)
typedef void(*PFNGLGETPATHCOMMANDSNVPROC)(GLuint,GLubyte*);
#endif
#if !defined(PFNGLGETPATHCOORDSNVPROC)
typedef void(*PFNGLGETPATHCOORDSNVPROC)(GLuint,GLfloat*);
#endif
#if !defined(PFNGLGETPATHDASHARRAYNVPROC)
typedef void(*PFNGLGETPATHDASHARRAYNVPROC)(GLuint,GLfloat*);
#endif
#if !defined(PFNGLGETPATHMETRICRANGENVPROC)
typedef void(*PFNGLGETPATHMETRICRANGENVPROC)(GLbitfield,GLuint,GLsizei,GLsizei,GLfloat*);
#endif
#if !defined(PFNGLGETPATHMETRICSNVPROC)
typedef void(*PFNGLGETPATHMETRICSNVPROC)(GLbitfield,GLsizei,GLenum,const void*,GLuint,GLsizei,GLfloat*);
#endif
#if !defined(PFNGLGETPATHPARAMETERFVNVPROC)
typedef void(*PFNGLGETPATHPARAMETERFVNVPROC)(GLuint,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETPATHPARAMETERIVNVPROC)
typedef void(*PFNGLGETPATHPARAMETERIVNVPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETPATHSPACINGNVPROC)
typedef void(*PFNGLGETPATHSPACINGNVPROC)(GLenum,GLsizei,GLenum,const void*,GLuint,GLfloat,GLfloat,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETPATHTEXGENFVNVPROC)
typedef void(*PFNGLGETPATHTEXGENFVNVPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETPATHTEXGENIVNVPROC)
typedef void(*PFNGLGETPATHTEXGENIVNVPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETPERFCOUNTERINFOINTELPROC)
typedef void(*PFNGLGETPERFCOUNTERINFOINTELPROC)(GLuint,GLuint,GLuint,GLchar*,GLuint,GLchar*,GLuint*,GLuint*,GLuint*,GLuint*,GLuint64*);
#endif
#if !defined(PFNGLGETPERFMONITORCOUNTERDATAAMDPROC)
typedef void(*PFNGLGETPERFMONITORCOUNTERDATAAMDPROC)(GLuint,GLenum,GLsizei,GLuint*,GLint*);
#endif
#if !defined(PFNGLGETPERFMONITORCOUNTERINFOAMDPROC)
typedef void(*PFNGLGETPERFMONITORCOUNTERINFOAMDPROC)(GLuint,GLuint,GLenum,void*);
#endif
#if !defined(PFNGLGETPERFMONITORCOUNTERSAMDPROC)
typedef void(*PFNGLGETPERFMONITORCOUNTERSAMDPROC)(GLuint,GLint*,GLint*,GLsizei,GLuint*);
#endif
#if !defined(PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC)
typedef void(*PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC)(GLuint,GLuint,GLsizei,GLsizei*,GLchar*);
#endif
#if !defined(PFNGLGETPERFMONITORGROUPSAMDPROC)
typedef void(*PFNGLGETPERFMONITORGROUPSAMDPROC)(GLint*,GLsizei,GLuint*);
#endif
#if !defined(PFNGLGETPERFMONITORGROUPSTRINGAMDPROC)
typedef void(*PFNGLGETPERFMONITORGROUPSTRINGAMDPROC)(GLuint,GLsizei,GLsizei*,GLchar*);
#endif
#if !defined(PFNGLGETPERFQUERYDATAINTELPROC)
typedef void(*PFNGLGETPERFQUERYDATAINTELPROC)(GLuint,GLuint,GLsizei,GLvoid*,GLuint*);
#endif
#if !defined(PFNGLGETPERFQUERYIDBYNAMEINTELPROC)
typedef void(*PFNGLGETPERFQUERYIDBYNAMEINTELPROC)(GLchar*,GLuint*);
#endif
#if !defined(PFNGLGETPERFQUERYINFOINTELPROC)
typedef void(*PFNGLGETPERFQUERYINFOINTELPROC)(GLuint,GLuint,GLchar*,GLuint*,GLuint*,GLuint*,GLuint*);
#endif
#if !defined(PFNGLGETPIXELMAPFVPROC)
typedef void(*PFNGLGETPIXELMAPFVPROC)(GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETPIXELMAPUIVPROC)
typedef void(*PFNGLGETPIXELMAPUIVPROC)(GLenum,GLuint*);
#endif
#if !defined(PFNGLGETPIXELMAPUSVPROC)
typedef void(*PFNGLGETPIXELMAPUSVPROC)(GLenum,GLushort*);
#endif
#if !defined(PFNGLGETPIXELMAPXVPROC)
typedef void(*PFNGLGETPIXELMAPXVPROC)(GLenum,GLint,GLfixed*);
#endif
#if !defined(PFNGLGETPIXELTEXGENPARAMETERFVSGISPROC)
typedef void(*PFNGLGETPIXELTEXGENPARAMETERFVSGISPROC)(GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETPIXELTEXGENPARAMETERIVSGISPROC)
typedef void(*PFNGLGETPIXELTEXGENPARAMETERIVSGISPROC)(GLenum,GLint*);
#endif
#if !defined(PFNGLGETPIXELTRANSFORMPARAMETERFVEXTPROC)
typedef void(*PFNGLGETPIXELTRANSFORMPARAMETERFVEXTPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETPIXELTRANSFORMPARAMETERIVEXTPROC)
typedef void(*PFNGLGETPIXELTRANSFORMPARAMETERIVEXTPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETPOINTERINDEXEDVEXTPROC)
typedef void(*PFNGLGETPOINTERINDEXEDVEXTPROC)(GLenum,GLuint,void**);
#endif
#if !defined(PFNGLGETPOINTERI_VEXTPROC)
typedef void(*PFNGLGETPOINTERI_VEXTPROC)(GLenum,GLuint,void**);
#endif
#if !defined(PFNGLGETPOINTERVEXTPROC)
typedef void(*PFNGLGETPOINTERVEXTPROC)(GLenum,void**);
#endif
#if !defined(PFNGLGETPOINTERVPROC)
typedef void(*PFNGLGETPOINTERVPROC)(GLenum,GLvoid**);
#endif
#if !defined(PFNGLGETPOLYGONSTIPPLEPROC)
typedef void(*PFNGLGETPOLYGONSTIPPLEPROC)(GLubyte*);
#endif
#if !defined(PFNGLGETPROGRAMBINARYPROC)
typedef void(*PFNGLGETPROGRAMBINARYPROC)(GLuint,GLsizei,GLsizei*,GLenum*,void*);
#endif
#if !defined(PFNGLGETPROGRAMENVPARAMETERDVARBPROC)
typedef void(*PFNGLGETPROGRAMENVPARAMETERDVARBPROC)(GLenum,GLuint,GLdouble*);
#endif
#if !defined(PFNGLGETPROGRAMENVPARAMETERFVARBPROC)
typedef void(*PFNGLGETPROGRAMENVPARAMETERFVARBPROC)(GLenum,GLuint,GLfloat*);
#endif
#if !defined(PFNGLGETPROGRAMENVPARAMETERIIVNVPROC)
typedef void(*PFNGLGETPROGRAMENVPARAMETERIIVNVPROC)(GLenum,GLuint,GLint*);
#endif
#if !defined(PFNGLGETPROGRAMENVPARAMETERIUIVNVPROC)
typedef void(*PFNGLGETPROGRAMENVPARAMETERIUIVNVPROC)(GLenum,GLuint,GLuint*);
#endif
#if !defined(PFNGLGETPROGRAMINFOLOGPROC)
typedef void(*PFNGLGETPROGRAMINFOLOGPROC)(GLuint,GLsizei,GLsizei*,GLchar*);
#endif
#if !defined(PFNGLGETPROGRAMINTERFACEIVPROC)
typedef void(*PFNGLGETPROGRAMINTERFACEIVPROC)(GLuint,GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETPROGRAMIVARBPROC)
typedef void(*PFNGLGETPROGRAMIVARBPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETPROGRAMIVPROC)
typedef void(*PFNGLGETPROGRAMIVPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETPROGRAMIVNVPROC)
typedef void(*PFNGLGETPROGRAMIVNVPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC)
typedef void(*PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC)(GLenum,GLuint,GLdouble*);
#endif
#if !defined(PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC)
typedef void(*PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC)(GLenum,GLuint,GLfloat*);
#endif
#if !defined(PFNGLGETPROGRAMLOCALPARAMETERIIVNVPROC)
typedef void(*PFNGLGETPROGRAMLOCALPARAMETERIIVNVPROC)(GLenum,GLuint,GLint*);
#endif
#if !defined(PFNGLGETPROGRAMLOCALPARAMETERIUIVNVPROC)
typedef void(*PFNGLGETPROGRAMLOCALPARAMETERIUIVNVPROC)(GLenum,GLuint,GLuint*);
#endif
#if !defined(PFNGLGETPROGRAMNAMEDPARAMETERDVNVPROC)
typedef void(*PFNGLGETPROGRAMNAMEDPARAMETERDVNVPROC)(GLuint,GLsizei,const GLubyte*,GLdouble*);
#endif
#if !defined(PFNGLGETPROGRAMNAMEDPARAMETERFVNVPROC)
typedef void(*PFNGLGETPROGRAMNAMEDPARAMETERFVNVPROC)(GLuint,GLsizei,const GLubyte*,GLfloat*);
#endif
#if !defined(PFNGLGETPROGRAMPARAMETERDVNVPROC)
typedef void(*PFNGLGETPROGRAMPARAMETERDVNVPROC)(GLenum,GLuint,GLenum,GLdouble*);
#endif
#if !defined(PFNGLGETPROGRAMPARAMETERFVNVPROC)
typedef void(*PFNGLGETPROGRAMPARAMETERFVNVPROC)(GLenum,GLuint,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETPROGRAMPIPELINEINFOLOGPROC)
typedef void(*PFNGLGETPROGRAMPIPELINEINFOLOGPROC)(GLuint,GLsizei,GLsizei*,GLchar*);
#endif
#if !defined(PFNGLGETPROGRAMPIPELINEIVPROC)
typedef void(*PFNGLGETPROGRAMPIPELINEIVPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETPROGRAMRESOURCEFVNVPROC)
typedef void(*PFNGLGETPROGRAMRESOURCEFVNVPROC)(GLuint,GLenum,GLuint,GLsizei,const GLenum*,GLsizei,GLsizei*,GLfloat*);
#endif
#if !defined(PFNGLGETPROGRAMRESOURCEIVPROC)
typedef void(*PFNGLGETPROGRAMRESOURCEIVPROC)(GLuint,GLenum,GLuint,GLsizei,const GLenum*,GLsizei,GLsizei*,GLint*);
#endif
#if !defined(PFNGLGETPROGRAMRESOURCENAMEPROC)
typedef void(*PFNGLGETPROGRAMRESOURCENAMEPROC)(GLuint,GLenum,GLuint,GLsizei,GLsizei*,GLchar*);
#endif
#if !defined(PFNGLGETPROGRAMSTAGEIVPROC)
typedef void(*PFNGLGETPROGRAMSTAGEIVPROC)(GLuint,GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETPROGRAMSTRINGARBPROC)
typedef void(*PFNGLGETPROGRAMSTRINGARBPROC)(GLenum,GLenum,void*);
#endif
#if !defined(PFNGLGETPROGRAMSTRINGNVPROC)
typedef void(*PFNGLGETPROGRAMSTRINGNVPROC)(GLuint,GLenum,GLubyte*);
#endif
#if !defined(PFNGLGETPROGRAMSUBROUTINEPARAMETERUIVNVPROC)
typedef void(*PFNGLGETPROGRAMSUBROUTINEPARAMETERUIVNVPROC)(GLenum,GLuint,GLuint*);
#endif
#if !defined(PFNGLGETQUERYBUFFEROBJECTI64VPROC)
typedef void(*PFNGLGETQUERYBUFFEROBJECTI64VPROC)(GLuint,GLuint,GLenum,GLintptr);
#endif
#if !defined(PFNGLGETQUERYBUFFEROBJECTIVPROC)
typedef void(*PFNGLGETQUERYBUFFEROBJECTIVPROC)(GLuint,GLuint,GLenum,GLintptr);
#endif
#if !defined(PFNGLGETQUERYBUFFEROBJECTUI64VPROC)
typedef void(*PFNGLGETQUERYBUFFEROBJECTUI64VPROC)(GLuint,GLuint,GLenum,GLintptr);
#endif
#if !defined(PFNGLGETQUERYBUFFEROBJECTUIVPROC)
typedef void(*PFNGLGETQUERYBUFFEROBJECTUIVPROC)(GLuint,GLuint,GLenum,GLintptr);
#endif
#if !defined(PFNGLGETQUERYINDEXEDIVPROC)
typedef void(*PFNGLGETQUERYINDEXEDIVPROC)(GLenum,GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETQUERYIVARBPROC)
typedef void(*PFNGLGETQUERYIVARBPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETQUERYIVPROC)
typedef void(*PFNGLGETQUERYIVPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETQUERYOBJECTI64VEXTPROC)
typedef void(*PFNGLGETQUERYOBJECTI64VEXTPROC)(GLuint,GLenum,GLint64*);
#endif
#if !defined(PFNGLGETQUERYOBJECTI64VPROC)
typedef void(*PFNGLGETQUERYOBJECTI64VPROC)(GLuint,GLenum,GLint64*);
#endif
#if !defined(PFNGLGETQUERYOBJECTIVARBPROC)
typedef void(*PFNGLGETQUERYOBJECTIVARBPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETQUERYOBJECTIVPROC)
typedef void(*PFNGLGETQUERYOBJECTIVPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETQUERYOBJECTUI64VEXTPROC)
typedef void(*PFNGLGETQUERYOBJECTUI64VEXTPROC)(GLuint,GLenum,GLuint64*);
#endif
#if !defined(PFNGLGETQUERYOBJECTUI64VPROC)
typedef void(*PFNGLGETQUERYOBJECTUI64VPROC)(GLuint,GLenum,GLuint64*);
#endif
#if !defined(PFNGLGETQUERYOBJECTUIVARBPROC)
typedef void(*PFNGLGETQUERYOBJECTUIVARBPROC)(GLuint,GLenum,GLuint*);
#endif
#if !defined(PFNGLGETQUERYOBJECTUIVPROC)
typedef void(*PFNGLGETQUERYOBJECTUIVPROC)(GLuint,GLenum,GLuint*);
#endif
#if !defined(PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC)
typedef void(*PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETRENDERBUFFERPARAMETERIVPROC)
typedef void(*PFNGLGETRENDERBUFFERPARAMETERIVPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETSAMPLERPARAMETERFVPROC)
typedef void(*PFNGLGETSAMPLERPARAMETERFVPROC)(GLuint,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETSAMPLERPARAMETERIIVPROC)
typedef void(*PFNGLGETSAMPLERPARAMETERIIVPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETSAMPLERPARAMETERIUIVPROC)
typedef void(*PFNGLGETSAMPLERPARAMETERIUIVPROC)(GLuint,GLenum,GLuint*);
#endif
#if !defined(PFNGLGETSAMPLERPARAMETERIVPROC)
typedef void(*PFNGLGETSAMPLERPARAMETERIVPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETSEPARABLEFILTEREXTPROC)
typedef void(*PFNGLGETSEPARABLEFILTEREXTPROC)(GLenum,GLenum,GLenum,void*,void*,void*);
#endif
#if !defined(PFNGLGETSEPARABLEFILTERPROC)
typedef void(*PFNGLGETSEPARABLEFILTERPROC)(GLenum,GLenum,GLenum,GLvoid*,GLvoid*,GLvoid*);
#endif
#if !defined(PFNGLGETSHADERINFOLOGPROC)
typedef void(*PFNGLGETSHADERINFOLOGPROC)(GLuint,GLsizei,GLsizei*,GLchar*);
#endif
#if !defined(PFNGLGETSHADERIVPROC)
typedef void(*PFNGLGETSHADERIVPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETSHADERPRECISIONFORMATPROC)
typedef void(*PFNGLGETSHADERPRECISIONFORMATPROC)(GLenum,GLenum,GLint*,GLint*);
#endif
#if !defined(PFNGLGETSHADERSOURCEARBPROC)
typedef void(*PFNGLGETSHADERSOURCEARBPROC)(GLhandleARB,GLsizei,GLsizei*,GLcharARB*);
#endif
#if !defined(PFNGLGETSHADERSOURCEPROC)
typedef void(*PFNGLGETSHADERSOURCEPROC)(GLuint,GLsizei,GLsizei*,GLchar*);
#endif
#if !defined(PFNGLGETSHARPENTEXFUNCSGISPROC)
typedef void(*PFNGLGETSHARPENTEXFUNCSGISPROC)(GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETSYNCIVPROC)
typedef void(*PFNGLGETSYNCIVPROC)(GLsync,GLenum,GLsizei,GLsizei*,GLint*);
#endif
#if !defined(PFNGLGETTEXBUMPPARAMETERFVATIPROC)
typedef void(*PFNGLGETTEXBUMPPARAMETERFVATIPROC)(GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETTEXBUMPPARAMETERIVATIPROC)
typedef void(*PFNGLGETTEXBUMPPARAMETERIVATIPROC)(GLenum,GLint*);
#endif
#if !defined(PFNGLGETTEXENVFVPROC)
typedef void(*PFNGLGETTEXENVFVPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETTEXENVIVPROC)
typedef void(*PFNGLGETTEXENVIVPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETTEXENVXVOESPROC)
typedef void(*PFNGLGETTEXENVXVOESPROC)(GLenum,GLenum,GLfixed*);
#endif
#if !defined(PFNGLGETTEXFILTERFUNCSGISPROC)
typedef void(*PFNGLGETTEXFILTERFUNCSGISPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETTEXGENDVPROC)
typedef void(*PFNGLGETTEXGENDVPROC)(GLenum,GLenum,GLdouble*);
#endif
#if !defined(PFNGLGETTEXGENFVPROC)
typedef void(*PFNGLGETTEXGENFVPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETTEXGENIVPROC)
typedef void(*PFNGLGETTEXGENIVPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETTEXGENXVOESPROC)
typedef void(*PFNGLGETTEXGENXVOESPROC)(GLenum,GLenum,GLfixed*);
#endif
#if !defined(PFNGLGETTEXIMAGEPROC)
typedef void(*PFNGLGETTEXIMAGEPROC)(GLenum,GLint,GLenum,GLenum,GLvoid*);
#endif
#if !defined(PFNGLGETTEXLEVELPARAMETERFVPROC)
typedef void(*PFNGLGETTEXLEVELPARAMETERFVPROC)(GLenum,GLint,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETTEXLEVELPARAMETERIVPROC)
typedef void(*PFNGLGETTEXLEVELPARAMETERIVPROC)(GLenum,GLint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETTEXLEVELPARAMETERXVOESPROC)
typedef void(*PFNGLGETTEXLEVELPARAMETERXVOESPROC)(GLenum,GLint,GLenum,GLfixed*);
#endif
#if !defined(PFNGLGETTEXPARAMETERFVPROC)
typedef void(*PFNGLGETTEXPARAMETERFVPROC)(GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETTEXPARAMETERIIVEXTPROC)
typedef void(*PFNGLGETTEXPARAMETERIIVEXTPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETTEXPARAMETERIIVPROC)
typedef void(*PFNGLGETTEXPARAMETERIIVPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETTEXPARAMETERIUIVEXTPROC)
typedef void(*PFNGLGETTEXPARAMETERIUIVEXTPROC)(GLenum,GLenum,GLuint*);
#endif
#if !defined(PFNGLGETTEXPARAMETERIUIVPROC)
typedef void(*PFNGLGETTEXPARAMETERIUIVPROC)(GLenum,GLenum,GLuint*);
#endif
#if !defined(PFNGLGETTEXPARAMETERIVPROC)
typedef void(*PFNGLGETTEXPARAMETERIVPROC)(GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETTEXPARAMETERPOINTERVAPPLEPROC)
typedef void(*PFNGLGETTEXPARAMETERPOINTERVAPPLEPROC)(GLenum,GLenum,void**);
#endif
#if !defined(PFNGLGETTEXPARAMETERXVOESPROC)
typedef void(*PFNGLGETTEXPARAMETERXVOESPROC)(GLenum,GLenum,GLfixed*);
#endif
#if !defined(PFNGLGETTEXTUREIMAGEEXTPROC)
typedef void(*PFNGLGETTEXTUREIMAGEEXTPROC)(GLuint,GLenum,GLint,GLenum,GLenum,void*);
#endif
#if !defined(PFNGLGETTEXTUREIMAGEPROC)
typedef void(*PFNGLGETTEXTUREIMAGEPROC)(GLuint,GLint,GLenum,GLenum,GLsizei,void*);
#endif
#if !defined(PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC)
typedef void(*PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC)(GLuint,GLenum,GLint,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETTEXTURELEVELPARAMETERFVPROC)
typedef void(*PFNGLGETTEXTURELEVELPARAMETERFVPROC)(GLuint,GLint,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC)
typedef void(*PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC)(GLuint,GLenum,GLint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETTEXTURELEVELPARAMETERIVPROC)
typedef void(*PFNGLGETTEXTURELEVELPARAMETERIVPROC)(GLuint,GLint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETTEXTUREPARAMETERFVEXTPROC)
typedef void(*PFNGLGETTEXTUREPARAMETERFVEXTPROC)(GLuint,GLenum,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETTEXTUREPARAMETERFVPROC)
typedef void(*PFNGLGETTEXTUREPARAMETERFVPROC)(GLuint,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETTEXTUREPARAMETERIIVEXTPROC)
typedef void(*PFNGLGETTEXTUREPARAMETERIIVEXTPROC)(GLuint,GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETTEXTUREPARAMETERIIVPROC)
typedef void(*PFNGLGETTEXTUREPARAMETERIIVPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETTEXTUREPARAMETERIUIVEXTPROC)
typedef void(*PFNGLGETTEXTUREPARAMETERIUIVEXTPROC)(GLuint,GLenum,GLenum,GLuint*);
#endif
#if !defined(PFNGLGETTEXTUREPARAMETERIUIVPROC)
typedef void(*PFNGLGETTEXTUREPARAMETERIUIVPROC)(GLuint,GLenum,GLuint*);
#endif
#if !defined(PFNGLGETTEXTUREPARAMETERIVEXTPROC)
typedef void(*PFNGLGETTEXTUREPARAMETERIVEXTPROC)(GLuint,GLenum,GLenum,GLint*);
#endif
#if !defined(PFNGLGETTEXTUREPARAMETERIVPROC)
typedef void(*PFNGLGETTEXTUREPARAMETERIVPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETTEXTURESUBIMAGEPROC)
typedef void(*PFNGLGETTEXTURESUBIMAGEPROC)(GLuint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,GLsizei,void*);
#endif
#if !defined(PFNGLGETTRACKMATRIXIVNVPROC)
typedef void(*PFNGLGETTRACKMATRIXIVNVPROC)(GLenum,GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETTRANSFORMFEEDBACKI64_VPROC)
typedef void(*PFNGLGETTRANSFORMFEEDBACKI64_VPROC)(GLuint,GLenum,GLuint,GLint64*);
#endif
#if !defined(PFNGLGETTRANSFORMFEEDBACKIVPROC)
typedef void(*PFNGLGETTRANSFORMFEEDBACKIVPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETTRANSFORMFEEDBACKI_VPROC)
typedef void(*PFNGLGETTRANSFORMFEEDBACKI_VPROC)(GLuint,GLenum,GLuint,GLint*);
#endif
#if !defined(PFNGLGETTRANSFORMFEEDBACKVARYINGEXTPROC)
typedef void(*PFNGLGETTRANSFORMFEEDBACKVARYINGEXTPROC)(GLuint,GLuint,GLsizei,GLsizei*,GLsizei*,GLenum*,GLchar*);
#endif
#if !defined(PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)
typedef void(*PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)(GLuint,GLuint,GLsizei,GLsizei*,GLsizei*,GLenum*,GLchar*);
#endif
#if !defined(PFNGLGETTRANSFORMFEEDBACKVARYINGNVPROC)
typedef void(*PFNGLGETTRANSFORMFEEDBACKVARYINGNVPROC)(GLuint,GLuint,GLint*);
#endif
#if !defined(PFNGLGETUNIFORMDVPROC)
typedef void(*PFNGLGETUNIFORMDVPROC)(GLuint,GLint,GLdouble*);
#endif
#if !defined(PFNGLGETUNIFORMFVARBPROC)
typedef void(*PFNGLGETUNIFORMFVARBPROC)(GLhandleARB,GLint,GLfloat*);
#endif
#if !defined(PFNGLGETUNIFORMFVPROC)
typedef void(*PFNGLGETUNIFORMFVPROC)(GLuint,GLint,GLfloat*);
#endif
#if !defined(PFNGLGETUNIFORMI64VARBPROC)
typedef void(*PFNGLGETUNIFORMI64VARBPROC)(GLuint,GLint,GLint64*);
#endif
#if !defined(PFNGLGETUNIFORMI64VNVPROC)
typedef void(*PFNGLGETUNIFORMI64VNVPROC)(GLuint,GLint,GLint64EXT*);
#endif
#if !defined(PFNGLGETUNIFORMINDICESPROC)
typedef void(*PFNGLGETUNIFORMINDICESPROC)(GLuint,GLsizei,const GLchar*const*,GLuint*);
#endif
#if !defined(PFNGLGETUNIFORMIVARBPROC)
typedef void(*PFNGLGETUNIFORMIVARBPROC)(GLhandleARB,GLint,GLint*);
#endif
#if !defined(PFNGLGETUNIFORMIVPROC)
typedef void(*PFNGLGETUNIFORMIVPROC)(GLuint,GLint,GLint*);
#endif
#if !defined(PFNGLGETUNIFORMSUBROUTINEUIVPROC)
typedef void(*PFNGLGETUNIFORMSUBROUTINEUIVPROC)(GLenum,GLint,GLuint*);
#endif
#if !defined(PFNGLGETUNIFORMUI64VARBPROC)
typedef void(*PFNGLGETUNIFORMUI64VARBPROC)(GLuint,GLint,GLuint64*);
#endif
#if !defined(PFNGLGETUNIFORMUI64VNVPROC)
typedef void(*PFNGLGETUNIFORMUI64VNVPROC)(GLuint,GLint,GLuint64EXT*);
#endif
#if !defined(PFNGLGETUNIFORMUIVEXTPROC)
typedef void(*PFNGLGETUNIFORMUIVEXTPROC)(GLuint,GLint,GLuint*);
#endif
#if !defined(PFNGLGETUNIFORMUIVPROC)
typedef void(*PFNGLGETUNIFORMUIVPROC)(GLuint,GLint,GLuint*);
#endif
#if !defined(PFNGLGETVARIANTARRAYOBJECTFVATIPROC)
typedef void(*PFNGLGETVARIANTARRAYOBJECTFVATIPROC)(GLuint,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETVARIANTARRAYOBJECTIVATIPROC)
typedef void(*PFNGLGETVARIANTARRAYOBJECTIVATIPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETVARIANTBOOLEANVEXTPROC)
typedef void(*PFNGLGETVARIANTBOOLEANVEXTPROC)(GLuint,GLenum,GLboolean*);
#endif
#if !defined(PFNGLGETVARIANTFLOATVEXTPROC)
typedef void(*PFNGLGETVARIANTFLOATVEXTPROC)(GLuint,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETVARIANTINTEGERVEXTPROC)
typedef void(*PFNGLGETVARIANTINTEGERVEXTPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETVARIANTPOINTERVEXTPROC)
typedef void(*PFNGLGETVARIANTPOINTERVEXTPROC)(GLuint,GLenum,void**);
#endif
#if !defined(PFNGLGETVERTEXARRAYINDEXED64IVPROC)
typedef void(*PFNGLGETVERTEXARRAYINDEXED64IVPROC)(GLuint,GLuint,GLenum,GLint64*);
#endif
#if !defined(PFNGLGETVERTEXARRAYINDEXEDIVPROC)
typedef void(*PFNGLGETVERTEXARRAYINDEXEDIVPROC)(GLuint,GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETVERTEXARRAYINTEGERI_VEXTPROC)
typedef void(*PFNGLGETVERTEXARRAYINTEGERI_VEXTPROC)(GLuint,GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETVERTEXARRAYINTEGERVEXTPROC)
typedef void(*PFNGLGETVERTEXARRAYINTEGERVEXTPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETVERTEXARRAYIVPROC)
typedef void(*PFNGLGETVERTEXARRAYIVPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETVERTEXARRAYPOINTERI_VEXTPROC)
typedef void(*PFNGLGETVERTEXARRAYPOINTERI_VEXTPROC)(GLuint,GLuint,GLenum,void**);
#endif
#if !defined(PFNGLGETVERTEXARRAYPOINTERVEXTPROC)
typedef void(*PFNGLGETVERTEXARRAYPOINTERVEXTPROC)(GLuint,GLenum,void**);
#endif
#if !defined(PFNGLGETVERTEXATTRIBARRAYOBJECTFVATIPROC)
typedef void(*PFNGLGETVERTEXATTRIBARRAYOBJECTFVATIPROC)(GLuint,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETVERTEXATTRIBARRAYOBJECTIVATIPROC)
typedef void(*PFNGLGETVERTEXATTRIBARRAYOBJECTIVATIPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETVERTEXATTRIBDVARBPROC)
typedef void(*PFNGLGETVERTEXATTRIBDVARBPROC)(GLuint,GLenum,GLdouble*);
#endif
#if !defined(PFNGLGETVERTEXATTRIBDVPROC)
typedef void(*PFNGLGETVERTEXATTRIBDVPROC)(GLuint,GLenum,GLdouble*);
#endif
#if !defined(PFNGLGETVERTEXATTRIBDVNVPROC)
typedef void(*PFNGLGETVERTEXATTRIBDVNVPROC)(GLuint,GLenum,GLdouble*);
#endif
#if !defined(PFNGLGETVERTEXATTRIBFVARBPROC)
typedef void(*PFNGLGETVERTEXATTRIBFVARBPROC)(GLuint,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETVERTEXATTRIBFVPROC)
typedef void(*PFNGLGETVERTEXATTRIBFVPROC)(GLuint,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETVERTEXATTRIBFVNVPROC)
typedef void(*PFNGLGETVERTEXATTRIBFVNVPROC)(GLuint,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETVERTEXATTRIBIIVEXTPROC)
typedef void(*PFNGLGETVERTEXATTRIBIIVEXTPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETVERTEXATTRIBIIVPROC)
typedef void(*PFNGLGETVERTEXATTRIBIIVPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETVERTEXATTRIBIUIVEXTPROC)
typedef void(*PFNGLGETVERTEXATTRIBIUIVEXTPROC)(GLuint,GLenum,GLuint*);
#endif
#if !defined(PFNGLGETVERTEXATTRIBIUIVPROC)
typedef void(*PFNGLGETVERTEXATTRIBIUIVPROC)(GLuint,GLenum,GLuint*);
#endif
#if !defined(PFNGLGETVERTEXATTRIBIVARBPROC)
typedef void(*PFNGLGETVERTEXATTRIBIVARBPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETVERTEXATTRIBIVPROC)
typedef void(*PFNGLGETVERTEXATTRIBIVPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETVERTEXATTRIBIVNVPROC)
typedef void(*PFNGLGETVERTEXATTRIBIVNVPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETVERTEXATTRIBLDVEXTPROC)
typedef void(*PFNGLGETVERTEXATTRIBLDVEXTPROC)(GLuint,GLenum,GLdouble*);
#endif
#if !defined(PFNGLGETVERTEXATTRIBLDVPROC)
typedef void(*PFNGLGETVERTEXATTRIBLDVPROC)(GLuint,GLenum,GLdouble*);
#endif
#if !defined(PFNGLGETVERTEXATTRIBLI64VNVPROC)
typedef void(*PFNGLGETVERTEXATTRIBLI64VNVPROC)(GLuint,GLenum,GLint64EXT*);
#endif
#if !defined(PFNGLGETVERTEXATTRIBLUI64VARBPROC)
typedef void(*PFNGLGETVERTEXATTRIBLUI64VARBPROC)(GLuint,GLenum,GLuint64EXT*);
#endif
#if !defined(PFNGLGETVERTEXATTRIBLUI64VNVPROC)
typedef void(*PFNGLGETVERTEXATTRIBLUI64VNVPROC)(GLuint,GLenum,GLuint64EXT*);
#endif
#if !defined(PFNGLGETVERTEXATTRIBPOINTERVARBPROC)
typedef void(*PFNGLGETVERTEXATTRIBPOINTERVARBPROC)(GLuint,GLenum,void**);
#endif
#if !defined(PFNGLGETVERTEXATTRIBPOINTERVPROC)
typedef void(*PFNGLGETVERTEXATTRIBPOINTERVPROC)(GLuint,GLenum,void**);
#endif
#if !defined(PFNGLGETVERTEXATTRIBPOINTERVNVPROC)
typedef void(*PFNGLGETVERTEXATTRIBPOINTERVNVPROC)(GLuint,GLenum,void**);
#endif
#if !defined(PFNGLGETVIDEOCAPTUREIVNVPROC)
typedef void(*PFNGLGETVIDEOCAPTUREIVNVPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETVIDEOCAPTURESTREAMDVNVPROC)
typedef void(*PFNGLGETVIDEOCAPTURESTREAMDVNVPROC)(GLuint,GLuint,GLenum,GLdouble*);
#endif
#if !defined(PFNGLGETVIDEOCAPTURESTREAMFVNVPROC)
typedef void(*PFNGLGETVIDEOCAPTURESTREAMFVNVPROC)(GLuint,GLuint,GLenum,GLfloat*);
#endif
#if !defined(PFNGLGETVIDEOCAPTURESTREAMIVNVPROC)
typedef void(*PFNGLGETVIDEOCAPTURESTREAMIVNVPROC)(GLuint,GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETVIDEOI64VNVPROC)
typedef void(*PFNGLGETVIDEOI64VNVPROC)(GLuint,GLenum,GLint64EXT*);
#endif
#if !defined(PFNGLGETVIDEOIVNVPROC)
typedef void(*PFNGLGETVIDEOIVNVPROC)(GLuint,GLenum,GLint*);
#endif
#if !defined(PFNGLGETVIDEOUI64VNVPROC)
typedef void(*PFNGLGETVIDEOUI64VNVPROC)(GLuint,GLenum,GLuint64EXT*);
#endif
#if !defined(PFNGLGETVIDEOUIVNVPROC)
typedef void(*PFNGLGETVIDEOUIVNVPROC)(GLuint,GLenum,GLuint*);
#endif
#if !defined(PFNGLGLOBALALPHAFACTORBSUNPROC)
typedef void(*PFNGLGLOBALALPHAFACTORBSUNPROC)(GLbyte);
#endif
#if !defined(PFNGLGLOBALALPHAFACTORDSUNPROC)
typedef void(*PFNGLGLOBALALPHAFACTORDSUNPROC)(GLdouble);
#endif
#if !defined(PFNGLGLOBALALPHAFACTORFSUNPROC)
typedef void(*PFNGLGLOBALALPHAFACTORFSUNPROC)(GLfloat);
#endif
#if !defined(PFNGLGLOBALALPHAFACTORISUNPROC)
typedef void(*PFNGLGLOBALALPHAFACTORISUNPROC)(GLint);
#endif
#if !defined(PFNGLGLOBALALPHAFACTORSSUNPROC)
typedef void(*PFNGLGLOBALALPHAFACTORSSUNPROC)(GLshort);
#endif
#if !defined(PFNGLGLOBALALPHAFACTORUBSUNPROC)
typedef void(*PFNGLGLOBALALPHAFACTORUBSUNPROC)(GLubyte);
#endif
#if !defined(PFNGLGLOBALALPHAFACTORUISUNPROC)
typedef void(*PFNGLGLOBALALPHAFACTORUISUNPROC)(GLuint);
#endif
#if !defined(PFNGLGLOBALALPHAFACTORUSSUNPROC)
typedef void(*PFNGLGLOBALALPHAFACTORUSSUNPROC)(GLushort);
#endif
#if !defined(PFNGLHINTPROC)
typedef void(*PFNGLHINTPROC)(GLenum,GLenum);
#endif
#if !defined(PFNGLHINTPGIPROC)
typedef void(*PFNGLHINTPGIPROC)(GLenum,GLint);
#endif
#if !defined(PFNGLHISTOGRAMEXTPROC)
typedef void(*PFNGLHISTOGRAMEXTPROC)(GLenum,GLsizei,GLenum,GLboolean);
#endif
#if !defined(PFNGLHISTOGRAMPROC)
typedef void(*PFNGLHISTOGRAMPROC)(GLenum,GLsizei,GLenum,GLboolean);
#endif
#if !defined(PFNGLIGLOOINTERFACESGIXPROC)
typedef void(*PFNGLIGLOOINTERFACESGIXPROC)(GLenum,const void*);
#endif
#if !defined(PFNGLIMAGETRANSFORMPARAMETERFHPPROC)
typedef void(*PFNGLIMAGETRANSFORMPARAMETERFHPPROC)(GLenum,GLenum,GLfloat);
#endif
#if !defined(PFNGLIMAGETRANSFORMPARAMETERFVHPPROC)
typedef void(*PFNGLIMAGETRANSFORMPARAMETERFVHPPROC)(GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLIMAGETRANSFORMPARAMETERIHPPROC)
typedef void(*PFNGLIMAGETRANSFORMPARAMETERIHPPROC)(GLenum,GLenum,GLint);
#endif
#if !defined(PFNGLIMAGETRANSFORMPARAMETERIVHPPROC)
typedef void(*PFNGLIMAGETRANSFORMPARAMETERIVHPPROC)(GLenum,GLenum,const GLint*);
#endif
#if !defined(PFNGLINDEXDPROC)
typedef void(*PFNGLINDEXDPROC)(GLdouble);
#endif
#if !defined(PFNGLINDEXDVPROC)
typedef void(*PFNGLINDEXDVPROC)(const GLdouble*);
#endif
#if !defined(PFNGLINDEXFPROC)
typedef void(*PFNGLINDEXFPROC)(GLfloat);
#endif
#if !defined(PFNGLINDEXFORMATNVPROC)
typedef void(*PFNGLINDEXFORMATNVPROC)(GLenum,GLsizei);
#endif
#if !defined(PFNGLINDEXFUNCEXTPROC)
typedef void(*PFNGLINDEXFUNCEXTPROC)(GLenum,GLclampf);
#endif
#if !defined(PFNGLINDEXFVPROC)
typedef void(*PFNGLINDEXFVPROC)(const GLfloat*);
#endif
#if !defined(PFNGLINDEXIPROC)
typedef void(*PFNGLINDEXIPROC)(GLint);
#endif
#if !defined(PFNGLINDEXIVPROC)
typedef void(*PFNGLINDEXIVPROC)(const GLint*);
#endif
#if !defined(PFNGLINDEXMASKPROC)
typedef void(*PFNGLINDEXMASKPROC)(GLuint);
#endif
#if !defined(PFNGLINDEXMATERIALEXTPROC)
typedef void(*PFNGLINDEXMATERIALEXTPROC)(GLenum,GLenum);
#endif
#if !defined(PFNGLINDEXPOINTEREXTPROC)
typedef void(*PFNGLINDEXPOINTEREXTPROC)(GLenum,GLsizei,GLsizei,const void*);
#endif
#if !defined(PFNGLINDEXPOINTERPROC)
typedef void(*PFNGLINDEXPOINTERPROC)(GLenum,GLsizei,const GLvoid*);
#endif
#if !defined(PFNGLINDEXPOINTERLISTIBMPROC)
typedef void(*PFNGLINDEXPOINTERLISTIBMPROC)(GLenum,GLint,const void**,GLint);
#endif
#if !defined(PFNGLINDEXSPROC)
typedef void(*PFNGLINDEXSPROC)(GLshort);
#endif
#if !defined(PFNGLINDEXSVPROC)
typedef void(*PFNGLINDEXSVPROC)(const GLshort*);
#endif
#if !defined(PFNGLINDEXUBPROC)
typedef void(*PFNGLINDEXUBPROC)(GLubyte);
#endif
#if !defined(PFNGLINDEXUBVPROC)
typedef void(*PFNGLINDEXUBVPROC)(const GLubyte*);
#endif
#if !defined(PFNGLINDEXXOESPROC)
typedef void(*PFNGLINDEXXOESPROC)(GLfixed);
#endif
#if !defined(PFNGLINDEXXVOESPROC)
typedef void(*PFNGLINDEXXVOESPROC)(const GLfixed*);
#endif
#if !defined(PFNGLINITNAMESPROC)
typedef void(*PFNGLINITNAMESPROC)();
#endif
#if !defined(PFNGLINSERTCOMPONENTEXTPROC)
typedef void(*PFNGLINSERTCOMPONENTEXTPROC)(GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLINSERTEVENTMARKEREXTPROC)
typedef void(*PFNGLINSERTEVENTMARKEREXTPROC)(GLsizei,const GLchar*);
#endif
#if !defined(PFNGLINSTRUMENTSBUFFERSGIXPROC)
typedef void(*PFNGLINSTRUMENTSBUFFERSGIXPROC)(GLsizei,GLint*);
#endif
#if !defined(PFNGLINTERLEAVEDARRAYSPROC)
typedef void(*PFNGLINTERLEAVEDARRAYSPROC)(GLenum,GLsizei,const GLvoid*);
#endif
#if !defined(PFNGLINTERPOLATEPATHSNVPROC)
typedef void(*PFNGLINTERPOLATEPATHSNVPROC)(GLuint,GLuint,GLuint,GLfloat);
#endif
#if !defined(PFNGLINVALIDATEBUFFERDATAPROC)
typedef void(*PFNGLINVALIDATEBUFFERDATAPROC)(GLuint);
#endif
#if !defined(PFNGLINVALIDATEBUFFERSUBDATAPROC)
typedef void(*PFNGLINVALIDATEBUFFERSUBDATAPROC)(GLuint,GLintptr,GLsizeiptr);
#endif
#if !defined(PFNGLINVALIDATEFRAMEBUFFERPROC)
typedef void(*PFNGLINVALIDATEFRAMEBUFFERPROC)(GLenum,GLsizei,const GLenum*);
#endif
#if !defined(PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC)
typedef void(*PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC)(GLuint,GLsizei,const GLenum*);
#endif
#if !defined(PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC)
typedef void(*PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC)(GLuint,GLsizei,const GLenum*,GLint,GLint,GLsizei,GLsizei);
#endif
#if !defined(PFNGLINVALIDATESUBFRAMEBUFFERPROC)
typedef void(*PFNGLINVALIDATESUBFRAMEBUFFERPROC)(GLenum,GLsizei,const GLenum*,GLint,GLint,GLsizei,GLsizei);
#endif
#if !defined(PFNGLINVALIDATETEXIMAGEPROC)
typedef void(*PFNGLINVALIDATETEXIMAGEPROC)(GLuint,GLint);
#endif
#if !defined(PFNGLINVALIDATETEXSUBIMAGEPROC)
typedef void(*PFNGLINVALIDATETEXSUBIMAGEPROC)(GLuint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei);
#endif
#if !defined(PFNGLLABELOBJECTEXTPROC)
typedef void(*PFNGLLABELOBJECTEXTPROC)(GLenum,GLuint,GLsizei,const GLchar*);
#endif
#if !defined(PFNGLLIGHTENVISGIXPROC)
typedef void(*PFNGLLIGHTENVISGIXPROC)(GLenum,GLint);
#endif
#if !defined(PFNGLLIGHTFPROC)
typedef void(*PFNGLLIGHTFPROC)(GLenum,GLenum,GLfloat);
#endif
#if !defined(PFNGLLIGHTFVPROC)
typedef void(*PFNGLLIGHTFVPROC)(GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLLIGHTIPROC)
typedef void(*PFNGLLIGHTIPROC)(GLenum,GLenum,GLint);
#endif
#if !defined(PFNGLLIGHTIVPROC)
typedef void(*PFNGLLIGHTIVPROC)(GLenum,GLenum,const GLint*);
#endif
#if !defined(PFNGLLIGHTMODELFPROC)
typedef void(*PFNGLLIGHTMODELFPROC)(GLenum,GLfloat);
#endif
#if !defined(PFNGLLIGHTMODELFVPROC)
typedef void(*PFNGLLIGHTMODELFVPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLLIGHTMODELIPROC)
typedef void(*PFNGLLIGHTMODELIPROC)(GLenum,GLint);
#endif
#if !defined(PFNGLLIGHTMODELIVPROC)
typedef void(*PFNGLLIGHTMODELIVPROC)(GLenum,const GLint*);
#endif
#if !defined(PFNGLLIGHTMODELXOESPROC)
typedef void(*PFNGLLIGHTMODELXOESPROC)(GLenum,GLfixed);
#endif
#if !defined(PFNGLLIGHTMODELXVOESPROC)
typedef void(*PFNGLLIGHTMODELXVOESPROC)(GLenum,const GLfixed*);
#endif
#if !defined(PFNGLLIGHTXOESPROC)
typedef void(*PFNGLLIGHTXOESPROC)(GLenum,GLenum,GLfixed);
#endif
#if !defined(PFNGLLIGHTXVOESPROC)
typedef void(*PFNGLLIGHTXVOESPROC)(GLenum,GLenum,const GLfixed*);
#endif
#if !defined(PFNGLLINESTIPPLEPROC)
typedef void(*PFNGLLINESTIPPLEPROC)(GLint,GLushort);
#endif
#if !defined(PFNGLLINEWIDTHPROC)
typedef void(*PFNGLLINEWIDTHPROC)(GLfloat);
#endif
#if !defined(PFNGLLINEWIDTHXOESPROC)
typedef void(*PFNGLLINEWIDTHXOESPROC)(GLfixed);
#endif
#if !defined(PFNGLLINKPROGRAMARBPROC)
typedef void(*PFNGLLINKPROGRAMARBPROC)(GLhandleARB);
#endif
#if !defined(PFNGLLINKPROGRAMPROC)
typedef void(*PFNGLLINKPROGRAMPROC)(GLuint);
#endif
#if !defined(PFNGLLISTBASEPROC)
typedef void(*PFNGLLISTBASEPROC)(GLuint);
#endif
#if !defined(PFNGLLISTDRAWCOMMANDSSTATESCLIENTNVPROC)
typedef void(*PFNGLLISTDRAWCOMMANDSSTATESCLIENTNVPROC)(GLuint,GLuint,const void**,const GLsizei*,const GLuint*,const GLuint*,GLuint);
#endif
#if !defined(PFNGLLISTPARAMETERFSGIXPROC)
typedef void(*PFNGLLISTPARAMETERFSGIXPROC)(GLuint,GLenum,GLfloat);
#endif
#if !defined(PFNGLLISTPARAMETERFVSGIXPROC)
typedef void(*PFNGLLISTPARAMETERFVSGIXPROC)(GLuint,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLLISTPARAMETERISGIXPROC)
typedef void(*PFNGLLISTPARAMETERISGIXPROC)(GLuint,GLenum,GLint);
#endif
#if !defined(PFNGLLISTPARAMETERIVSGIXPROC)
typedef void(*PFNGLLISTPARAMETERIVSGIXPROC)(GLuint,GLenum,const GLint*);
#endif
#if !defined(PFNGLLOADIDENTITYPROC)
typedef void(*PFNGLLOADIDENTITYPROC)();
#endif
#if !defined(PFNGLLOADIDENTITYDEFORMATIONMAPSGIXPROC)
typedef void(*PFNGLLOADIDENTITYDEFORMATIONMAPSGIXPROC)(GLbitfield);
#endif
#if !defined(PFNGLLOADMATRIXDPROC)
typedef void(*PFNGLLOADMATRIXDPROC)(const GLdouble*);
#endif
#if !defined(PFNGLLOADMATRIXFPROC)
typedef void(*PFNGLLOADMATRIXFPROC)(const GLfloat*);
#endif
#if !defined(PFNGLLOADMATRIXXOESPROC)
typedef void(*PFNGLLOADMATRIXXOESPROC)(const GLfixed*);
#endif
#if !defined(PFNGLLOADNAMEPROC)
typedef void(*PFNGLLOADNAMEPROC)(GLuint);
#endif
#if !defined(PFNGLLOADPROGRAMNVPROC)
typedef void(*PFNGLLOADPROGRAMNVPROC)(GLenum,GLuint,GLsizei,const GLubyte*);
#endif
#if !defined(PFNGLLOADTRANSPOSEMATRIXDARBPROC)
typedef void(*PFNGLLOADTRANSPOSEMATRIXDARBPROC)(const GLdouble*);
#endif
#if !defined(PFNGLLOADTRANSPOSEMATRIXDPROC)
typedef void(*PFNGLLOADTRANSPOSEMATRIXDPROC)(const GLdouble);
#endif
#if !defined(PFNGLLOADTRANSPOSEMATRIXFARBPROC)
typedef void(*PFNGLLOADTRANSPOSEMATRIXFARBPROC)(const GLfloat*);
#endif
#if !defined(PFNGLLOADTRANSPOSEMATRIXFPROC)
typedef void(*PFNGLLOADTRANSPOSEMATRIXFPROC)(const GLfloat);
#endif
#if !defined(PFNGLLOADTRANSPOSEMATRIXXOESPROC)
typedef void(*PFNGLLOADTRANSPOSEMATRIXXOESPROC)(const GLfixed*);
#endif
#if !defined(PFNGLLOCKARRAYSEXTPROC)
typedef void(*PFNGLLOCKARRAYSEXTPROC)(GLint,GLsizei);
#endif
#if !defined(PFNGLLOGICOPPROC)
typedef void(*PFNGLLOGICOPPROC)(GLenum);
#endif
#if !defined(PFNGLMAKEBUFFERNONRESIDENTNVPROC)
typedef void(*PFNGLMAKEBUFFERNONRESIDENTNVPROC)(GLenum);
#endif
#if !defined(PFNGLMAKEBUFFERRESIDENTNVPROC)
typedef void(*PFNGLMAKEBUFFERRESIDENTNVPROC)(GLenum,GLenum);
#endif
#if !defined(PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC)
typedef void(*PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC)(GLuint64);
#endif
#if !defined(PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC)
typedef void(*PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC)(GLuint64);
#endif
#if !defined(PFNGLMAKEIMAGEHANDLERESIDENTARBPROC)
typedef void(*PFNGLMAKEIMAGEHANDLERESIDENTARBPROC)(GLuint64,GLenum);
#endif
#if !defined(PFNGLMAKEIMAGEHANDLERESIDENTNVPROC)
typedef void(*PFNGLMAKEIMAGEHANDLERESIDENTNVPROC)(GLuint64,GLenum);
#endif
#if !defined(PFNGLMAKENAMEDBUFFERNONRESIDENTNVPROC)
typedef void(*PFNGLMAKENAMEDBUFFERNONRESIDENTNVPROC)(GLuint);
#endif
#if !defined(PFNGLMAKENAMEDBUFFERRESIDENTNVPROC)
typedef void(*PFNGLMAKENAMEDBUFFERRESIDENTNVPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC)
typedef void(*PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC)(GLuint64);
#endif
#if !defined(PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC)
typedef void(*PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC)(GLuint64);
#endif
#if !defined(PFNGLMAKETEXTUREHANDLERESIDENTARBPROC)
typedef void(*PFNGLMAKETEXTUREHANDLERESIDENTARBPROC)(GLuint64);
#endif
#if !defined(PFNGLMAKETEXTUREHANDLERESIDENTNVPROC)
typedef void(*PFNGLMAKETEXTUREHANDLERESIDENTNVPROC)(GLuint64);
#endif
#if !defined(PFNGLMAP1DPROC)
typedef void(*PFNGLMAP1DPROC)(GLenum,GLdouble,GLdouble,GLint,GLint,const GLdouble*);
#endif
#if !defined(PFNGLMAP1FPROC)
typedef void(*PFNGLMAP1FPROC)(GLenum,GLfloat,GLfloat,GLint,GLint,const GLfloat*);
#endif
#if !defined(PFNGLMAP1XOESPROC)
typedef void(*PFNGLMAP1XOESPROC)(GLenum,GLfixed,GLfixed,GLint,GLint,GLfixed);
#endif
#if !defined(PFNGLMAP2DPROC)
typedef void(*PFNGLMAP2DPROC)(GLenum,GLdouble,GLdouble,GLint,GLint,GLdouble,GLdouble,GLint,GLint,const GLdouble*);
#endif
#if !defined(PFNGLMAP2FPROC)
typedef void(*PFNGLMAP2FPROC)(GLenum,GLfloat,GLfloat,GLint,GLint,GLfloat,GLfloat,GLint,GLint,const GLfloat*);
#endif
#if !defined(PFNGLMAP2XOESPROC)
typedef void(*PFNGLMAP2XOESPROC)(GLenum,GLfixed,GLfixed,GLint,GLint,GLfixed,GLfixed,GLint,GLint,GLfixed);
#endif
#if !defined(PFNGLMAPBUFFERARBPROC)
typedef void*(*PFNGLMAPBUFFERARBPROC)(GLenum,GLenum);
#endif
#if !defined(PFNGLMAPBUFFERPROC)
typedef void*(*PFNGLMAPBUFFERPROC)(GLenum,GLenum);
#endif
#if !defined(PFNGLMAPBUFFERRANGEPROC)
typedef void*(*PFNGLMAPBUFFERRANGEPROC)(GLenum,GLintptr,GLsizeiptr,GLbitfield);
#endif
#if !defined(PFNGLMAPCONTROLPOINTSNVPROC)
typedef void(*PFNGLMAPCONTROLPOINTSNVPROC)(GLenum,GLuint,GLenum,GLsizei,GLsizei,GLint,GLint,GLboolean,const void*);
#endif
#if !defined(PFNGLMAPGRID1DPROC)
typedef void(*PFNGLMAPGRID1DPROC)(GLint,GLdouble,GLdouble);
#endif
#if !defined(PFNGLMAPGRID1FPROC)
typedef void(*PFNGLMAPGRID1FPROC)(GLint,GLfloat,GLfloat);
#endif
#if !defined(PFNGLMAPGRID1XOESPROC)
typedef void(*PFNGLMAPGRID1XOESPROC)(GLint,GLfixed,GLfixed);
#endif
#if !defined(PFNGLMAPGRID2DPROC)
typedef void(*PFNGLMAPGRID2DPROC)(GLint,GLdouble,GLdouble,GLint,GLdouble,GLdouble);
#endif
#if !defined(PFNGLMAPGRID2FPROC)
typedef void(*PFNGLMAPGRID2FPROC)(GLint,GLfloat,GLfloat,GLint,GLfloat,GLfloat);
#endif
#if !defined(PFNGLMAPGRID2XOESPROC)
typedef void(*PFNGLMAPGRID2XOESPROC)(GLint,GLfixed,GLfixed,GLfixed,GLfixed);
#endif
#if !defined(PFNGLMAPNAMEDBUFFEREXTPROC)
typedef void*(*PFNGLMAPNAMEDBUFFEREXTPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLMAPNAMEDBUFFERPROC)
typedef void*(*PFNGLMAPNAMEDBUFFERPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLMAPNAMEDBUFFERRANGEEXTPROC)
typedef void*(*PFNGLMAPNAMEDBUFFERRANGEEXTPROC)(GLuint,GLintptr,GLsizeiptr,GLbitfield);
#endif
#if !defined(PFNGLMAPNAMEDBUFFERRANGEPROC)
typedef void*(*PFNGLMAPNAMEDBUFFERRANGEPROC)(GLuint,GLintptr,GLsizeiptr,GLbitfield);
#endif
#if !defined(PFNGLMAPOBJECTBUFFERATIPROC)
typedef void*(*PFNGLMAPOBJECTBUFFERATIPROC)(GLuint);
#endif
#if !defined(PFNGLMAPPARAMETERFVNVPROC)
typedef void(*PFNGLMAPPARAMETERFVNVPROC)(GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMAPPARAMETERIVNVPROC)
typedef void(*PFNGLMAPPARAMETERIVNVPROC)(GLenum,GLenum,const GLint*);
#endif
#if !defined(PFNGLMAPTEXTURE2DINTELPROC)
typedef void*(*PFNGLMAPTEXTURE2DINTELPROC)(GLuint,GLint,GLbitfield,GLint*,GLenum*);
#endif
#if !defined(PFNGLMAPVERTEXATTRIB1DAPPLEPROC)
typedef void(*PFNGLMAPVERTEXATTRIB1DAPPLEPROC)(GLuint,GLuint,GLdouble,GLdouble,GLint,GLint,const GLdouble*);
#endif
#if !defined(PFNGLMAPVERTEXATTRIB1FAPPLEPROC)
typedef void(*PFNGLMAPVERTEXATTRIB1FAPPLEPROC)(GLuint,GLuint,GLfloat,GLfloat,GLint,GLint,const GLfloat*);
#endif
#if !defined(PFNGLMAPVERTEXATTRIB2DAPPLEPROC)
typedef void(*PFNGLMAPVERTEXATTRIB2DAPPLEPROC)(GLuint,GLuint,GLdouble,GLdouble,GLint,GLint,GLdouble,GLdouble,GLint,GLint,const GLdouble*);
#endif
#if !defined(PFNGLMAPVERTEXATTRIB2FAPPLEPROC)
typedef void(*PFNGLMAPVERTEXATTRIB2FAPPLEPROC)(GLuint,GLuint,GLfloat,GLfloat,GLint,GLint,GLfloat,GLfloat,GLint,GLint,const GLfloat*);
#endif
#if !defined(PFNGLMATERIALFPROC)
typedef void(*PFNGLMATERIALFPROC)(GLenum,GLenum,GLfloat);
#endif
#if !defined(PFNGLMATERIALFVPROC)
typedef void(*PFNGLMATERIALFVPROC)(GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMATERIALIPROC)
typedef void(*PFNGLMATERIALIPROC)(GLenum,GLenum,GLint);
#endif
#if !defined(PFNGLMATERIALIVPROC)
typedef void(*PFNGLMATERIALIVPROC)(GLenum,GLenum,const GLint*);
#endif
#if !defined(PFNGLMATERIALXOESPROC)
typedef void(*PFNGLMATERIALXOESPROC)(GLenum,GLenum,GLfixed);
#endif
#if !defined(PFNGLMATERIALXVOESPROC)
typedef void(*PFNGLMATERIALXVOESPROC)(GLenum,GLenum,const GLfixed*);
#endif
#if !defined(PFNGLMATRIXFRUSTUMEXTPROC)
typedef void(*PFNGLMATRIXFRUSTUMEXTPROC)(GLenum,GLdouble,GLdouble,GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLMATRIXINDEXPOINTERARBPROC)
typedef void(*PFNGLMATRIXINDEXPOINTERARBPROC)(GLint,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLMATRIXINDEXUBVARBPROC)
typedef void(*PFNGLMATRIXINDEXUBVARBPROC)(GLint,const GLubyte*);
#endif
#if !defined(PFNGLMATRIXINDEXUIVARBPROC)
typedef void(*PFNGLMATRIXINDEXUIVARBPROC)(GLint,const GLuint*);
#endif
#if !defined(PFNGLMATRIXINDEXUSVARBPROC)
typedef void(*PFNGLMATRIXINDEXUSVARBPROC)(GLint,const GLushort*);
#endif
#if !defined(PFNGLMATRIXLOAD3X2FNVPROC)
typedef void(*PFNGLMATRIXLOAD3X2FNVPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMATRIXLOAD3X3FNVPROC)
typedef void(*PFNGLMATRIXLOAD3X3FNVPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMATRIXLOADDEXTPROC)
typedef void(*PFNGLMATRIXLOADDEXTPROC)(GLenum,const GLdouble*);
#endif
#if !defined(PFNGLMATRIXLOADFEXTPROC)
typedef void(*PFNGLMATRIXLOADFEXTPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMATRIXLOADIDENTITYEXTPROC)
typedef void(*PFNGLMATRIXLOADIDENTITYEXTPROC)(GLenum);
#endif
#if !defined(PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC)
typedef void(*PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMATRIXLOADTRANSPOSEDEXTPROC)
typedef void(*PFNGLMATRIXLOADTRANSPOSEDEXTPROC)(GLenum,const GLdouble*);
#endif
#if !defined(PFNGLMATRIXLOADTRANSPOSEFEXTPROC)
typedef void(*PFNGLMATRIXLOADTRANSPOSEFEXTPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMATRIXMODEPROC)
typedef void(*PFNGLMATRIXMODEPROC)(GLenum);
#endif
#if !defined(PFNGLMATRIXMULT3X2FNVPROC)
typedef void(*PFNGLMATRIXMULT3X2FNVPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMATRIXMULT3X3FNVPROC)
typedef void(*PFNGLMATRIXMULT3X3FNVPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMATRIXMULTDEXTPROC)
typedef void(*PFNGLMATRIXMULTDEXTPROC)(GLenum,const GLdouble*);
#endif
#if !defined(PFNGLMATRIXMULTFEXTPROC)
typedef void(*PFNGLMATRIXMULTFEXTPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC)
typedef void(*PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMATRIXMULTTRANSPOSEDEXTPROC)
typedef void(*PFNGLMATRIXMULTTRANSPOSEDEXTPROC)(GLenum,const GLdouble*);
#endif
#if !defined(PFNGLMATRIXMULTTRANSPOSEFEXTPROC)
typedef void(*PFNGLMATRIXMULTTRANSPOSEFEXTPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMATRIXORTHOEXTPROC)
typedef void(*PFNGLMATRIXORTHOEXTPROC)(GLenum,GLdouble,GLdouble,GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLMATRIXPOPEXTPROC)
typedef void(*PFNGLMATRIXPOPEXTPROC)(GLenum);
#endif
#if !defined(PFNGLMATRIXPUSHEXTPROC)
typedef void(*PFNGLMATRIXPUSHEXTPROC)(GLenum);
#endif
#if !defined(PFNGLMATRIXROTATEDEXTPROC)
typedef void(*PFNGLMATRIXROTATEDEXTPROC)(GLenum,GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLMATRIXROTATEFEXTPROC)
typedef void(*PFNGLMATRIXROTATEFEXTPROC)(GLenum,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLMATRIXSCALEDEXTPROC)
typedef void(*PFNGLMATRIXSCALEDEXTPROC)(GLenum,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLMATRIXSCALEFEXTPROC)
typedef void(*PFNGLMATRIXSCALEFEXTPROC)(GLenum,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLMATRIXTRANSLATEDEXTPROC)
typedef void(*PFNGLMATRIXTRANSLATEDEXTPROC)(GLenum,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLMATRIXTRANSLATEFEXTPROC)
typedef void(*PFNGLMATRIXTRANSLATEFEXTPROC)(GLenum,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLMAXSHADERCOMPILERTHREADSARBPROC)
typedef void(*PFNGLMAXSHADERCOMPILERTHREADSARBPROC)(GLuint);
#endif
#if !defined(PFNGLMEMORYBARRIERBYREGIONPROC)
typedef void(*PFNGLMEMORYBARRIERBYREGIONPROC)(GLbitfield);
#endif
#if !defined(PFNGLMEMORYBARRIEREXTPROC)
typedef void(*PFNGLMEMORYBARRIEREXTPROC)(GLbitfield);
#endif
#if !defined(PFNGLMEMORYBARRIERPROC)
typedef void(*PFNGLMEMORYBARRIERPROC)(GLbitfield);
#endif
#if !defined(PFNGLMINMAXEXTPROC)
typedef void(*PFNGLMINMAXEXTPROC)(GLenum,GLenum,GLboolean);
#endif
#if !defined(PFNGLMINMAXPROC)
typedef void(*PFNGLMINMAXPROC)(GLenum,GLenum,GLboolean);
#endif
#if !defined(PFNGLMINSAMPLESHADINGARBPROC)
typedef void(*PFNGLMINSAMPLESHADINGARBPROC)(GLfloat);
#endif
#if !defined(PFNGLMINSAMPLESHADINGPROC)
typedef void(*PFNGLMINSAMPLESHADINGPROC)(GLfloat);
#endif
#if !defined(PFNGLMULTIDRAWARRAYSEXTPROC)
typedef void(*PFNGLMULTIDRAWARRAYSEXTPROC)(GLenum,const GLint*,const GLsizei*,GLsizei);
#endif
#if !defined(PFNGLMULTIDRAWARRAYSPROC)
typedef void(*PFNGLMULTIDRAWARRAYSPROC)(GLenum,const GLint*,const GLsizei*,GLsizei);
#endif
#if !defined(PFNGLMULTIDRAWARRAYSINDIRECTAMDPROC)
typedef void(*PFNGLMULTIDRAWARRAYSINDIRECTAMDPROC)(GLenum,const void*,GLsizei,GLsizei);
#endif
#if !defined(PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSCOUNTNVPROC)
typedef void(*PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSCOUNTNVPROC)(GLenum,const void*,GLsizei,GLsizei,GLsizei,GLint);
#endif
#if !defined(PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSNVPROC)
typedef void(*PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSNVPROC)(GLenum,const void*,GLsizei,GLsizei,GLint);
#endif
#if !defined(PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC)
typedef void(*PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC)(GLenum,GLintptr,GLintptr,GLsizei,GLsizei);
#endif
#if !defined(PFNGLMULTIDRAWARRAYSINDIRECTPROC)
typedef void(*PFNGLMULTIDRAWARRAYSINDIRECTPROC)(GLenum,const void*,GLsizei,GLsizei);
#endif
#if !defined(PFNGLMULTIDRAWELEMENTARRAYAPPLEPROC)
typedef void(*PFNGLMULTIDRAWELEMENTARRAYAPPLEPROC)(GLenum,const GLint*,const GLsizei*,GLsizei);
#endif
#if !defined(PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)
typedef void(*PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)(GLenum,const GLsizei*,GLenum,const void*const*,GLsizei,const GLint*);
#endif
#if !defined(PFNGLMULTIDRAWELEMENTSEXTPROC)
typedef void(*PFNGLMULTIDRAWELEMENTSEXTPROC)(GLenum,const GLsizei*,GLenum,const void*const*,GLsizei);
#endif
#if !defined(PFNGLMULTIDRAWELEMENTSPROC)
typedef void(*PFNGLMULTIDRAWELEMENTSPROC)(GLenum,const GLsizei*,GLenum,const void*const*,GLsizei);
#endif
#if !defined(PFNGLMULTIDRAWELEMENTSINDIRECTAMDPROC)
typedef void(*PFNGLMULTIDRAWELEMENTSINDIRECTAMDPROC)(GLenum,GLenum,const void*,GLsizei,GLsizei);
#endif
#if !defined(PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSCOUNTNVPROC)
typedef void(*PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSCOUNTNVPROC)(GLenum,GLenum,const void*,GLsizei,GLsizei,GLsizei,GLint);
#endif
#if !defined(PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSNVPROC)
typedef void(*PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSNVPROC)(GLenum,GLenum,const void*,GLsizei,GLsizei,GLint);
#endif
#if !defined(PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC)
typedef void(*PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC)(GLenum,GLenum,GLintptr,GLintptr,GLsizei,GLsizei);
#endif
#if !defined(PFNGLMULTIDRAWELEMENTSINDIRECTPROC)
typedef void(*PFNGLMULTIDRAWELEMENTSINDIRECTPROC)(GLenum,GLenum,const void*,GLsizei,GLsizei);
#endif
#if !defined(PFNGLMULTIDRAWRANGEELEMENTARRAYAPPLEPROC)
typedef void(*PFNGLMULTIDRAWRANGEELEMENTARRAYAPPLEPROC)(GLenum,GLuint,GLuint,const GLint*,const GLsizei*,GLsizei);
#endif
#if !defined(PFNGLMULTIMODEDRAWARRAYSIBMPROC)
typedef void(*PFNGLMULTIMODEDRAWARRAYSIBMPROC)(const GLenum*,const GLint*,const GLsizei*,GLsizei,GLint);
#endif
#if !defined(PFNGLMULTIMODEDRAWELEMENTSIBMPROC)
typedef void(*PFNGLMULTIMODEDRAWELEMENTSIBMPROC)(const GLenum*,const GLsizei*,GLenum,const void*const*,GLsizei,GLint);
#endif
#if !defined(PFNGLMULTITEXBUFFEREXTPROC)
typedef void(*PFNGLMULTITEXBUFFEREXTPROC)(GLenum,GLenum,GLenum,GLuint);
#endif
#if !defined(PFNGLMULTITEXCOORD1BOESPROC)
typedef void(*PFNGLMULTITEXCOORD1BOESPROC)(GLenum,GLbyte);
#endif
#if !defined(PFNGLMULTITEXCOORD1BVOESPROC)
typedef void(*PFNGLMULTITEXCOORD1BVOESPROC)(GLenum,const GLbyte*);
#endif
#if !defined(PFNGLMULTITEXCOORD1DARBPROC)
typedef void(*PFNGLMULTITEXCOORD1DARBPROC)(GLenum,GLdouble);
#endif
#if !defined(PFNGLMULTITEXCOORD1DPROC)
typedef void(*PFNGLMULTITEXCOORD1DPROC)(GLenum,GLdouble);
#endif
#if !defined(PFNGLMULTITEXCOORD1DVARBPROC)
typedef void(*PFNGLMULTITEXCOORD1DVARBPROC)(GLenum,const GLdouble*);
#endif
#if !defined(PFNGLMULTITEXCOORD1DVPROC)
typedef void(*PFNGLMULTITEXCOORD1DVPROC)(GLenum,const GLdouble*);
#endif
#if !defined(PFNGLMULTITEXCOORD1FARBPROC)
typedef void(*PFNGLMULTITEXCOORD1FARBPROC)(GLenum,GLfloat);
#endif
#if !defined(PFNGLMULTITEXCOORD1FPROC)
typedef void(*PFNGLMULTITEXCOORD1FPROC)(GLenum,GLfloat);
#endif
#if !defined(PFNGLMULTITEXCOORD1FVARBPROC)
typedef void(*PFNGLMULTITEXCOORD1FVARBPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMULTITEXCOORD1FVPROC)
typedef void(*PFNGLMULTITEXCOORD1FVPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMULTITEXCOORD1HNVPROC)
typedef void(*PFNGLMULTITEXCOORD1HNVPROC)(GLenum,GLhalfNV);
#endif
#if !defined(PFNGLMULTITEXCOORD1HVNVPROC)
typedef void(*PFNGLMULTITEXCOORD1HVNVPROC)(GLenum,const GLhalfNV*);
#endif
#if !defined(PFNGLMULTITEXCOORD1IARBPROC)
typedef void(*PFNGLMULTITEXCOORD1IARBPROC)(GLenum,GLint);
#endif
#if !defined(PFNGLMULTITEXCOORD1IPROC)
typedef void(*PFNGLMULTITEXCOORD1IPROC)(GLenum,GLint);
#endif
#if !defined(PFNGLMULTITEXCOORD1IVARBPROC)
typedef void(*PFNGLMULTITEXCOORD1IVARBPROC)(GLenum,const GLint*);
#endif
#if !defined(PFNGLMULTITEXCOORD1IVPROC)
typedef void(*PFNGLMULTITEXCOORD1IVPROC)(GLenum,const GLint*);
#endif
#if !defined(PFNGLMULTITEXCOORD1SARBPROC)
typedef void(*PFNGLMULTITEXCOORD1SARBPROC)(GLenum,GLshort);
#endif
#if !defined(PFNGLMULTITEXCOORD1SPROC)
typedef void(*PFNGLMULTITEXCOORD1SPROC)(GLenum,GLshort);
#endif
#if !defined(PFNGLMULTITEXCOORD1SVARBPROC)
typedef void(*PFNGLMULTITEXCOORD1SVARBPROC)(GLenum,const GLshort*);
#endif
#if !defined(PFNGLMULTITEXCOORD1SVPROC)
typedef void(*PFNGLMULTITEXCOORD1SVPROC)(GLenum,const GLshort*);
#endif
#if !defined(PFNGLMULTITEXCOORD1XOESPROC)
typedef void(*PFNGLMULTITEXCOORD1XOESPROC)(GLenum,GLfixed);
#endif
#if !defined(PFNGLMULTITEXCOORD1XVOESPROC)
typedef void(*PFNGLMULTITEXCOORD1XVOESPROC)(GLenum,const GLfixed*);
#endif
#if !defined(PFNGLMULTITEXCOORD2BOESPROC)
typedef void(*PFNGLMULTITEXCOORD2BOESPROC)(GLenum,GLbyte,GLbyte);
#endif
#if !defined(PFNGLMULTITEXCOORD2BVOESPROC)
typedef void(*PFNGLMULTITEXCOORD2BVOESPROC)(GLenum,const GLbyte*);
#endif
#if !defined(PFNGLMULTITEXCOORD2DARBPROC)
typedef void(*PFNGLMULTITEXCOORD2DARBPROC)(GLenum,GLdouble,GLdouble);
#endif
#if !defined(PFNGLMULTITEXCOORD2DPROC)
typedef void(*PFNGLMULTITEXCOORD2DPROC)(GLenum,GLdouble,GLdouble);
#endif
#if !defined(PFNGLMULTITEXCOORD2DVARBPROC)
typedef void(*PFNGLMULTITEXCOORD2DVARBPROC)(GLenum,const GLdouble*);
#endif
#if !defined(PFNGLMULTITEXCOORD2DVPROC)
typedef void(*PFNGLMULTITEXCOORD2DVPROC)(GLenum,const GLdouble*);
#endif
#if !defined(PFNGLMULTITEXCOORD2FARBPROC)
typedef void(*PFNGLMULTITEXCOORD2FARBPROC)(GLenum,GLfloat,GLfloat);
#endif
#if !defined(PFNGLMULTITEXCOORD2FPROC)
typedef void(*PFNGLMULTITEXCOORD2FPROC)(GLenum,GLfloat,GLfloat);
#endif
#if !defined(PFNGLMULTITEXCOORD2FVARBPROC)
typedef void(*PFNGLMULTITEXCOORD2FVARBPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMULTITEXCOORD2FVPROC)
typedef void(*PFNGLMULTITEXCOORD2FVPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMULTITEXCOORD2HNVPROC)
typedef void(*PFNGLMULTITEXCOORD2HNVPROC)(GLenum,GLhalfNV,GLhalfNV);
#endif
#if !defined(PFNGLMULTITEXCOORD2HVNVPROC)
typedef void(*PFNGLMULTITEXCOORD2HVNVPROC)(GLenum,const GLhalfNV*);
#endif
#if !defined(PFNGLMULTITEXCOORD2IARBPROC)
typedef void(*PFNGLMULTITEXCOORD2IARBPROC)(GLenum,GLint,GLint);
#endif
#if !defined(PFNGLMULTITEXCOORD2IPROC)
typedef void(*PFNGLMULTITEXCOORD2IPROC)(GLenum,GLint,GLint);
#endif
#if !defined(PFNGLMULTITEXCOORD2IVARBPROC)
typedef void(*PFNGLMULTITEXCOORD2IVARBPROC)(GLenum,const GLint*);
#endif
#if !defined(PFNGLMULTITEXCOORD2IVPROC)
typedef void(*PFNGLMULTITEXCOORD2IVPROC)(GLenum,const GLint*);
#endif
#if !defined(PFNGLMULTITEXCOORD2SARBPROC)
typedef void(*PFNGLMULTITEXCOORD2SARBPROC)(GLenum,GLshort,GLshort);
#endif
#if !defined(PFNGLMULTITEXCOORD2SPROC)
typedef void(*PFNGLMULTITEXCOORD2SPROC)(GLenum,GLshort,GLshort);
#endif
#if !defined(PFNGLMULTITEXCOORD2SVARBPROC)
typedef void(*PFNGLMULTITEXCOORD2SVARBPROC)(GLenum,const GLshort*);
#endif
#if !defined(PFNGLMULTITEXCOORD2SVPROC)
typedef void(*PFNGLMULTITEXCOORD2SVPROC)(GLenum,const GLshort*);
#endif
#if !defined(PFNGLMULTITEXCOORD2XOESPROC)
typedef void(*PFNGLMULTITEXCOORD2XOESPROC)(GLenum,GLfixed,GLfixed);
#endif
#if !defined(PFNGLMULTITEXCOORD2XVOESPROC)
typedef void(*PFNGLMULTITEXCOORD2XVOESPROC)(GLenum,const GLfixed*);
#endif
#if !defined(PFNGLMULTITEXCOORD3BOESPROC)
typedef void(*PFNGLMULTITEXCOORD3BOESPROC)(GLenum,GLbyte,GLbyte,GLbyte);
#endif
#if !defined(PFNGLMULTITEXCOORD3BVOESPROC)
typedef void(*PFNGLMULTITEXCOORD3BVOESPROC)(GLenum,const GLbyte*);
#endif
#if !defined(PFNGLMULTITEXCOORD3DARBPROC)
typedef void(*PFNGLMULTITEXCOORD3DARBPROC)(GLenum,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLMULTITEXCOORD3DPROC)
typedef void(*PFNGLMULTITEXCOORD3DPROC)(GLenum,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLMULTITEXCOORD3DVARBPROC)
typedef void(*PFNGLMULTITEXCOORD3DVARBPROC)(GLenum,const GLdouble*);
#endif
#if !defined(PFNGLMULTITEXCOORD3DVPROC)
typedef void(*PFNGLMULTITEXCOORD3DVPROC)(GLenum,const GLdouble*);
#endif
#if !defined(PFNGLMULTITEXCOORD3FARBPROC)
typedef void(*PFNGLMULTITEXCOORD3FARBPROC)(GLenum,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLMULTITEXCOORD3FPROC)
typedef void(*PFNGLMULTITEXCOORD3FPROC)(GLenum,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLMULTITEXCOORD3FVARBPROC)
typedef void(*PFNGLMULTITEXCOORD3FVARBPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMULTITEXCOORD3FVPROC)
typedef void(*PFNGLMULTITEXCOORD3FVPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMULTITEXCOORD3HNVPROC)
typedef void(*PFNGLMULTITEXCOORD3HNVPROC)(GLenum,GLhalfNV,GLhalfNV,GLhalfNV);
#endif
#if !defined(PFNGLMULTITEXCOORD3HVNVPROC)
typedef void(*PFNGLMULTITEXCOORD3HVNVPROC)(GLenum,const GLhalfNV*);
#endif
#if !defined(PFNGLMULTITEXCOORD3IARBPROC)
typedef void(*PFNGLMULTITEXCOORD3IARBPROC)(GLenum,GLint,GLint,GLint);
#endif
#if !defined(PFNGLMULTITEXCOORD3IPROC)
typedef void(*PFNGLMULTITEXCOORD3IPROC)(GLenum,GLint,GLint,GLint);
#endif
#if !defined(PFNGLMULTITEXCOORD3IVARBPROC)
typedef void(*PFNGLMULTITEXCOORD3IVARBPROC)(GLenum,const GLint*);
#endif
#if !defined(PFNGLMULTITEXCOORD3IVPROC)
typedef void(*PFNGLMULTITEXCOORD3IVPROC)(GLenum,const GLint*);
#endif
#if !defined(PFNGLMULTITEXCOORD3SARBPROC)
typedef void(*PFNGLMULTITEXCOORD3SARBPROC)(GLenum,GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLMULTITEXCOORD3SPROC)
typedef void(*PFNGLMULTITEXCOORD3SPROC)(GLenum,GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLMULTITEXCOORD3SVARBPROC)
typedef void(*PFNGLMULTITEXCOORD3SVARBPROC)(GLenum,const GLshort*);
#endif
#if !defined(PFNGLMULTITEXCOORD3SVPROC)
typedef void(*PFNGLMULTITEXCOORD3SVPROC)(GLenum,const GLshort*);
#endif
#if !defined(PFNGLMULTITEXCOORD3XOESPROC)
typedef void(*PFNGLMULTITEXCOORD3XOESPROC)(GLenum,GLfixed,GLfixed,GLfixed);
#endif
#if !defined(PFNGLMULTITEXCOORD3XVOESPROC)
typedef void(*PFNGLMULTITEXCOORD3XVOESPROC)(GLenum,const GLfixed*);
#endif
#if !defined(PFNGLMULTITEXCOORD4BOESPROC)
typedef void(*PFNGLMULTITEXCOORD4BOESPROC)(GLenum,GLbyte,GLbyte,GLbyte,GLbyte);
#endif
#if !defined(PFNGLMULTITEXCOORD4BVOESPROC)
typedef void(*PFNGLMULTITEXCOORD4BVOESPROC)(GLenum,const GLbyte*);
#endif
#if !defined(PFNGLMULTITEXCOORD4DARBPROC)
typedef void(*PFNGLMULTITEXCOORD4DARBPROC)(GLenum,GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLMULTITEXCOORD4DPROC)
typedef void(*PFNGLMULTITEXCOORD4DPROC)(GLenum,GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLMULTITEXCOORD4DVARBPROC)
typedef void(*PFNGLMULTITEXCOORD4DVARBPROC)(GLenum,const GLdouble*);
#endif
#if !defined(PFNGLMULTITEXCOORD4DVPROC)
typedef void(*PFNGLMULTITEXCOORD4DVPROC)(GLenum,const GLdouble*);
#endif
#if !defined(PFNGLMULTITEXCOORD4FARBPROC)
typedef void(*PFNGLMULTITEXCOORD4FARBPROC)(GLenum,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLMULTITEXCOORD4FPROC)
typedef void(*PFNGLMULTITEXCOORD4FPROC)(GLenum,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLMULTITEXCOORD4FVARBPROC)
typedef void(*PFNGLMULTITEXCOORD4FVARBPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMULTITEXCOORD4FVPROC)
typedef void(*PFNGLMULTITEXCOORD4FVPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMULTITEXCOORD4HNVPROC)
typedef void(*PFNGLMULTITEXCOORD4HNVPROC)(GLenum,GLhalfNV,GLhalfNV,GLhalfNV,GLhalfNV);
#endif
#if !defined(PFNGLMULTITEXCOORD4HVNVPROC)
typedef void(*PFNGLMULTITEXCOORD4HVNVPROC)(GLenum,const GLhalfNV*);
#endif
#if !defined(PFNGLMULTITEXCOORD4IARBPROC)
typedef void(*PFNGLMULTITEXCOORD4IARBPROC)(GLenum,GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLMULTITEXCOORD4IPROC)
typedef void(*PFNGLMULTITEXCOORD4IPROC)(GLenum,GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLMULTITEXCOORD4IVARBPROC)
typedef void(*PFNGLMULTITEXCOORD4IVARBPROC)(GLenum,const GLint*);
#endif
#if !defined(PFNGLMULTITEXCOORD4IVPROC)
typedef void(*PFNGLMULTITEXCOORD4IVPROC)(GLenum,const GLint*);
#endif
#if !defined(PFNGLMULTITEXCOORD4SARBPROC)
typedef void(*PFNGLMULTITEXCOORD4SARBPROC)(GLenum,GLshort,GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLMULTITEXCOORD4SPROC)
typedef void(*PFNGLMULTITEXCOORD4SPROC)(GLenum,GLshort,GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLMULTITEXCOORD4SVARBPROC)
typedef void(*PFNGLMULTITEXCOORD4SVARBPROC)(GLenum,const GLshort*);
#endif
#if !defined(PFNGLMULTITEXCOORD4SVPROC)
typedef void(*PFNGLMULTITEXCOORD4SVPROC)(GLenum,const GLshort*);
#endif
#if !defined(PFNGLMULTITEXCOORD4XOESPROC)
typedef void(*PFNGLMULTITEXCOORD4XOESPROC)(GLenum,GLfixed,GLfixed,GLfixed,GLfixed);
#endif
#if !defined(PFNGLMULTITEXCOORD4XVOESPROC)
typedef void(*PFNGLMULTITEXCOORD4XVOESPROC)(GLenum,const GLfixed*);
#endif
#if !defined(PFNGLMULTITEXCOORDP1UIPROC)
typedef void(*PFNGLMULTITEXCOORDP1UIPROC)(GLenum,GLenum,GLuint);
#endif
#if !defined(PFNGLMULTITEXCOORDP1UIVPROC)
typedef void(*PFNGLMULTITEXCOORDP1UIVPROC)(GLenum,GLenum,const GLuint*);
#endif
#if !defined(PFNGLMULTITEXCOORDP2UIPROC)
typedef void(*PFNGLMULTITEXCOORDP2UIPROC)(GLenum,GLenum,GLuint);
#endif
#if !defined(PFNGLMULTITEXCOORDP2UIVPROC)
typedef void(*PFNGLMULTITEXCOORDP2UIVPROC)(GLenum,GLenum,const GLuint*);
#endif
#if !defined(PFNGLMULTITEXCOORDP3UIPROC)
typedef void(*PFNGLMULTITEXCOORDP3UIPROC)(GLenum,GLenum,GLuint);
#endif
#if !defined(PFNGLMULTITEXCOORDP3UIVPROC)
typedef void(*PFNGLMULTITEXCOORDP3UIVPROC)(GLenum,GLenum,const GLuint*);
#endif
#if !defined(PFNGLMULTITEXCOORDP4UIPROC)
typedef void(*PFNGLMULTITEXCOORDP4UIPROC)(GLenum,GLenum,GLuint);
#endif
#if !defined(PFNGLMULTITEXCOORDP4UIVPROC)
typedef void(*PFNGLMULTITEXCOORDP4UIVPROC)(GLenum,GLenum,const GLuint*);
#endif
#if !defined(PFNGLMULTITEXCOORDPOINTEREXTPROC)
typedef void(*PFNGLMULTITEXCOORDPOINTEREXTPROC)(GLenum,GLint,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLMULTITEXENVFEXTPROC)
typedef void(*PFNGLMULTITEXENVFEXTPROC)(GLenum,GLenum,GLenum,GLfloat);
#endif
#if !defined(PFNGLMULTITEXENVFVEXTPROC)
typedef void(*PFNGLMULTITEXENVFVEXTPROC)(GLenum,GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMULTITEXENVIEXTPROC)
typedef void(*PFNGLMULTITEXENVIEXTPROC)(GLenum,GLenum,GLenum,GLint);
#endif
#if !defined(PFNGLMULTITEXENVIVEXTPROC)
typedef void(*PFNGLMULTITEXENVIVEXTPROC)(GLenum,GLenum,GLenum,const GLint*);
#endif
#if !defined(PFNGLMULTITEXGENDEXTPROC)
typedef void(*PFNGLMULTITEXGENDEXTPROC)(GLenum,GLenum,GLenum,GLdouble);
#endif
#if !defined(PFNGLMULTITEXGENDVEXTPROC)
typedef void(*PFNGLMULTITEXGENDVEXTPROC)(GLenum,GLenum,GLenum,const GLdouble*);
#endif
#if !defined(PFNGLMULTITEXGENFEXTPROC)
typedef void(*PFNGLMULTITEXGENFEXTPROC)(GLenum,GLenum,GLenum,GLfloat);
#endif
#if !defined(PFNGLMULTITEXGENFVEXTPROC)
typedef void(*PFNGLMULTITEXGENFVEXTPROC)(GLenum,GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMULTITEXGENIEXTPROC)
typedef void(*PFNGLMULTITEXGENIEXTPROC)(GLenum,GLenum,GLenum,GLint);
#endif
#if !defined(PFNGLMULTITEXGENIVEXTPROC)
typedef void(*PFNGLMULTITEXGENIVEXTPROC)(GLenum,GLenum,GLenum,const GLint*);
#endif
#if !defined(PFNGLMULTITEXIMAGE1DEXTPROC)
typedef void(*PFNGLMULTITEXIMAGE1DEXTPROC)(GLenum,GLenum,GLint,GLint,GLsizei,GLint,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLMULTITEXIMAGE2DEXTPROC)
typedef void(*PFNGLMULTITEXIMAGE2DEXTPROC)(GLenum,GLenum,GLint,GLint,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLMULTITEXIMAGE3DEXTPROC)
typedef void(*PFNGLMULTITEXIMAGE3DEXTPROC)(GLenum,GLenum,GLint,GLint,GLsizei,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLMULTITEXPARAMETERFEXTPROC)
typedef void(*PFNGLMULTITEXPARAMETERFEXTPROC)(GLenum,GLenum,GLenum,GLfloat);
#endif
#if !defined(PFNGLMULTITEXPARAMETERFVEXTPROC)
typedef void(*PFNGLMULTITEXPARAMETERFVEXTPROC)(GLenum,GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLMULTITEXPARAMETERIEXTPROC)
typedef void(*PFNGLMULTITEXPARAMETERIEXTPROC)(GLenum,GLenum,GLenum,GLint);
#endif
#if !defined(PFNGLMULTITEXPARAMETERIIVEXTPROC)
typedef void(*PFNGLMULTITEXPARAMETERIIVEXTPROC)(GLenum,GLenum,GLenum,const GLint*);
#endif
#if !defined(PFNGLMULTITEXPARAMETERIUIVEXTPROC)
typedef void(*PFNGLMULTITEXPARAMETERIUIVEXTPROC)(GLenum,GLenum,GLenum,const GLuint*);
#endif
#if !defined(PFNGLMULTITEXPARAMETERIVEXTPROC)
typedef void(*PFNGLMULTITEXPARAMETERIVEXTPROC)(GLenum,GLenum,GLenum,const GLint*);
#endif
#if !defined(PFNGLMULTITEXRENDERBUFFEREXTPROC)
typedef void(*PFNGLMULTITEXRENDERBUFFEREXTPROC)(GLenum,GLenum,GLuint);
#endif
#if !defined(PFNGLMULTITEXSUBIMAGE1DEXTPROC)
typedef void(*PFNGLMULTITEXSUBIMAGE1DEXTPROC)(GLenum,GLenum,GLint,GLint,GLsizei,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLMULTITEXSUBIMAGE2DEXTPROC)
typedef void(*PFNGLMULTITEXSUBIMAGE2DEXTPROC)(GLenum,GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLMULTITEXSUBIMAGE3DEXTPROC)
typedef void(*PFNGLMULTITEXSUBIMAGE3DEXTPROC)(GLenum,GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLMULTMATRIXDPROC)
typedef void(*PFNGLMULTMATRIXDPROC)(const GLdouble*);
#endif
#if !defined(PFNGLMULTMATRIXFPROC)
typedef void(*PFNGLMULTMATRIXFPROC)(const GLfloat*);
#endif
#if !defined(PFNGLMULTMATRIXXOESPROC)
typedef void(*PFNGLMULTMATRIXXOESPROC)(const GLfixed*);
#endif
#if !defined(PFNGLMULTTRANSPOSEMATRIXDARBPROC)
typedef void(*PFNGLMULTTRANSPOSEMATRIXDARBPROC)(const GLdouble*);
#endif
#if !defined(PFNGLMULTTRANSPOSEMATRIXDPROC)
typedef void(*PFNGLMULTTRANSPOSEMATRIXDPROC)(const GLdouble);
#endif
#if !defined(PFNGLMULTTRANSPOSEMATRIXFARBPROC)
typedef void(*PFNGLMULTTRANSPOSEMATRIXFARBPROC)(const GLfloat*);
#endif
#if !defined(PFNGLMULTTRANSPOSEMATRIXFPROC)
typedef void(*PFNGLMULTTRANSPOSEMATRIXFPROC)(const GLfloat);
#endif
#if !defined(PFNGLMULTTRANSPOSEMATRIXXOESPROC)
typedef void(*PFNGLMULTTRANSPOSEMATRIXXOESPROC)(const GLfixed*);
#endif
#if !defined(PFNGLNAMEDBUFFERDATAEXTPROC)
typedef void(*PFNGLNAMEDBUFFERDATAEXTPROC)(GLuint,GLsizeiptr,const void*,GLenum);
#endif
#if !defined(PFNGLNAMEDBUFFERDATAPROC)
typedef void(*PFNGLNAMEDBUFFERDATAPROC)(GLuint,GLsizeiptr,const void*,GLenum);
#endif
#if !defined(PFNGLNAMEDBUFFERPAGECOMMITMENTARBPROC)
typedef void(*PFNGLNAMEDBUFFERPAGECOMMITMENTARBPROC)(GLuint,GLintptr,GLsizeiptr,GLboolean);
#endif
#if !defined(PFNGLNAMEDBUFFERPAGECOMMITMENTEXTPROC)
typedef void(*PFNGLNAMEDBUFFERPAGECOMMITMENTEXTPROC)(GLuint,GLintptr,GLsizeiptr,GLboolean);
#endif
#if !defined(PFNGLNAMEDBUFFERSTORAGEEXTPROC)
typedef void(*PFNGLNAMEDBUFFERSTORAGEEXTPROC)(GLuint,GLsizeiptr,const void*,GLbitfield);
#endif
#if !defined(PFNGLNAMEDBUFFERSTORAGEPROC)
typedef void(*PFNGLNAMEDBUFFERSTORAGEPROC)(GLuint,GLsizeiptr,const void*,GLbitfield);
#endif
#if !defined(PFNGLNAMEDBUFFERSUBDATAEXTPROC)
typedef void(*PFNGLNAMEDBUFFERSUBDATAEXTPROC)(GLuint,GLintptr,GLsizeiptr,const void*);
#endif
#if !defined(PFNGLNAMEDBUFFERSUBDATAPROC)
typedef void(*PFNGLNAMEDBUFFERSUBDATAPROC)(GLuint,GLintptr,GLsizeiptr,const void*);
#endif
#if !defined(PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC)
typedef void(*PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC)(GLuint,GLuint,GLintptr,GLintptr,GLsizeiptr);
#endif
#if !defined(PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC)
typedef void(*PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC)
typedef void(*PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC)(GLuint,GLsizei,const GLenum*);
#endif
#if !defined(PFNGLNAMEDFRAMEBUFFERPARAMETERIEXTPROC)
typedef void(*PFNGLNAMEDFRAMEBUFFERPARAMETERIEXTPROC)(GLuint,GLenum,GLint);
#endif
#if !defined(PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC)
typedef void(*PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC)(GLuint,GLenum,GLint);
#endif
#if !defined(PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC)
typedef void(*PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC)
typedef void(*PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC)(GLuint,GLenum,GLenum,GLuint);
#endif
#if !defined(PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC)
typedef void(*PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC)(GLuint,GLenum,GLenum,GLuint);
#endif
#if !defined(PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVARBPROC)
typedef void(*PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVARBPROC)(GLuint,GLuint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC)
typedef void(*PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC)(GLuint,GLuint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC)
typedef void(*PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC)(GLuint,GLenum,GLenum,GLuint,GLint);
#endif
#if !defined(PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC)
typedef void(*PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC)(GLuint,GLenum,GLenum,GLuint,GLint);
#endif
#if !defined(PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC)
typedef void(*PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC)(GLuint,GLenum,GLenum,GLuint,GLint,GLint);
#endif
#if !defined(PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC)
typedef void(*PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC)(GLuint,GLenum,GLuint,GLint);
#endif
#if !defined(PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC)
typedef void(*PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC)(GLuint,GLenum,GLuint,GLint,GLenum);
#endif
#if !defined(PFNGLNAMEDFRAMEBUFFERTEXTUREPROC)
typedef void(*PFNGLNAMEDFRAMEBUFFERTEXTUREPROC)(GLuint,GLenum,GLuint,GLint);
#endif
#if !defined(PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC)
typedef void(*PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC)(GLuint,GLenum,GLuint,GLint,GLint);
#endif
#if !defined(PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC)
typedef void(*PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC)(GLuint,GLenum,GLuint,GLint,GLint);
#endif
#if !defined(PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC)
typedef void(*PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC)(GLuint,GLenum,GLuint,GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC)
typedef void(*PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC)(GLuint,GLenum,GLuint,const GLdouble*);
#endif
#if !defined(PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC)
typedef void(*PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC)(GLuint,GLenum,GLuint,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC)
typedef void(*PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC)(GLuint,GLenum,GLuint,const GLfloat*);
#endif
#if !defined(PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC)
typedef void(*PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC)(GLuint,GLenum,GLuint,GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC)
typedef void(*PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC)(GLuint,GLenum,GLuint,const GLint*);
#endif
#if !defined(PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC)
typedef void(*PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC)(GLuint,GLenum,GLuint,GLuint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC)
typedef void(*PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC)(GLuint,GLenum,GLuint,const GLuint*);
#endif
#if !defined(PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC)
typedef void(*PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC)(GLuint,GLenum,GLuint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC)
typedef void(*PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC)(GLuint,GLenum,GLuint,GLsizei,const GLint*);
#endif
#if !defined(PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC)
typedef void(*PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC)(GLuint,GLenum,GLuint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLNAMEDPROGRAMSTRINGEXTPROC)
typedef void(*PFNGLNAMEDPROGRAMSTRINGEXTPROC)(GLuint,GLenum,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC)
typedef void(*PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC)(GLuint,GLenum,GLsizei,GLsizei);
#endif
#if !defined(PFNGLNAMEDRENDERBUFFERSTORAGEPROC)
typedef void(*PFNGLNAMEDRENDERBUFFERSTORAGEPROC)(GLuint,GLenum,GLsizei,GLsizei);
#endif
#if !defined(PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC)
typedef void(*PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC)(GLuint,GLsizei,GLsizei,GLenum,GLsizei,GLsizei);
#endif
#if !defined(PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC)
typedef void(*PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC)(GLuint,GLsizei,GLenum,GLsizei,GLsizei);
#endif
#if !defined(PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC)
typedef void(*PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC)(GLuint,GLsizei,GLenum,GLsizei,GLsizei);
#endif
#if !defined(PFNGLNAMEDSTRINGARBPROC)
typedef void(*PFNGLNAMEDSTRINGARBPROC)(GLenum,GLint,const GLchar*,GLint,const GLchar*);
#endif
#if !defined(PFNGLNEWLISTPROC)
typedef void(*PFNGLNEWLISTPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLNORMAL3BPROC)
typedef void(*PFNGLNORMAL3BPROC)(GLbyte,GLbyte,GLbyte);
#endif
#if !defined(PFNGLNORMAL3BVPROC)
typedef void(*PFNGLNORMAL3BVPROC)(const GLbyte*);
#endif
#if !defined(PFNGLNORMAL3DPROC)
typedef void(*PFNGLNORMAL3DPROC)(GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLNORMAL3DVPROC)
typedef void(*PFNGLNORMAL3DVPROC)(const GLdouble*);
#endif
#if !defined(PFNGLNORMAL3FPROC)
typedef void(*PFNGLNORMAL3FPROC)(GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLNORMAL3FVPROC)
typedef void(*PFNGLNORMAL3FVPROC)(const GLfloat*);
#endif
#if !defined(PFNGLNORMAL3FVERTEX3FSUNPROC)
typedef void(*PFNGLNORMAL3FVERTEX3FSUNPROC)(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLNORMAL3FVERTEX3FVSUNPROC)
typedef void(*PFNGLNORMAL3FVERTEX3FVSUNPROC)(const GLfloat*,const GLfloat*);
#endif
#if !defined(PFNGLNORMAL3HNVPROC)
typedef void(*PFNGLNORMAL3HNVPROC)(GLhalfNV,GLhalfNV,GLhalfNV);
#endif
#if !defined(PFNGLNORMAL3HVNVPROC)
typedef void(*PFNGLNORMAL3HVNVPROC)(const GLhalfNV*);
#endif
#if !defined(PFNGLNORMAL3IPROC)
typedef void(*PFNGLNORMAL3IPROC)(GLint,GLint,GLint);
#endif
#if !defined(PFNGLNORMAL3IVPROC)
typedef void(*PFNGLNORMAL3IVPROC)(const GLint*);
#endif
#if !defined(PFNGLNORMAL3SPROC)
typedef void(*PFNGLNORMAL3SPROC)(GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLNORMAL3SVPROC)
typedef void(*PFNGLNORMAL3SVPROC)(const GLshort*);
#endif
#if !defined(PFNGLNORMAL3XOESPROC)
typedef void(*PFNGLNORMAL3XOESPROC)(GLfixed,GLfixed,GLfixed);
#endif
#if !defined(PFNGLNORMAL3XVOESPROC)
typedef void(*PFNGLNORMAL3XVOESPROC)(const GLfixed*);
#endif
#if !defined(PFNGLNORMALFORMATNVPROC)
typedef void(*PFNGLNORMALFORMATNVPROC)(GLenum,GLsizei);
#endif
#if !defined(PFNGLNORMALP3UIPROC)
typedef void(*PFNGLNORMALP3UIPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLNORMALP3UIVPROC)
typedef void(*PFNGLNORMALP3UIVPROC)(GLenum,const GLuint*);
#endif
#if !defined(PFNGLNORMALPOINTEREXTPROC)
typedef void(*PFNGLNORMALPOINTEREXTPROC)(GLenum,GLsizei,GLsizei,const void*);
#endif
#if !defined(PFNGLNORMALPOINTERPROC)
typedef void(*PFNGLNORMALPOINTERPROC)(GLenum,GLsizei,const GLvoid*);
#endif
#if !defined(PFNGLNORMALPOINTERLISTIBMPROC)
typedef void(*PFNGLNORMALPOINTERLISTIBMPROC)(GLenum,GLint,const void**,GLint);
#endif
#if !defined(PFNGLNORMALPOINTERVINTELPROC)
typedef void(*PFNGLNORMALPOINTERVINTELPROC)(GLenum,const void**);
#endif
#if !defined(PFNGLNORMALSTREAM3BATIPROC)
typedef void(*PFNGLNORMALSTREAM3BATIPROC)(GLenum,GLbyte,GLbyte,GLbyte);
#endif
#if !defined(PFNGLNORMALSTREAM3BVATIPROC)
typedef void(*PFNGLNORMALSTREAM3BVATIPROC)(GLenum,const GLbyte*);
#endif
#if !defined(PFNGLNORMALSTREAM3DATIPROC)
typedef void(*PFNGLNORMALSTREAM3DATIPROC)(GLenum,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLNORMALSTREAM3DVATIPROC)
typedef void(*PFNGLNORMALSTREAM3DVATIPROC)(GLenum,const GLdouble*);
#endif
#if !defined(PFNGLNORMALSTREAM3FATIPROC)
typedef void(*PFNGLNORMALSTREAM3FATIPROC)(GLenum,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLNORMALSTREAM3FVATIPROC)
typedef void(*PFNGLNORMALSTREAM3FVATIPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLNORMALSTREAM3IATIPROC)
typedef void(*PFNGLNORMALSTREAM3IATIPROC)(GLenum,GLint,GLint,GLint);
#endif
#if !defined(PFNGLNORMALSTREAM3IVATIPROC)
typedef void(*PFNGLNORMALSTREAM3IVATIPROC)(GLenum,const GLint*);
#endif
#if !defined(PFNGLNORMALSTREAM3SATIPROC)
typedef void(*PFNGLNORMALSTREAM3SATIPROC)(GLenum,GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLNORMALSTREAM3SVATIPROC)
typedef void(*PFNGLNORMALSTREAM3SVATIPROC)(GLenum,const GLshort*);
#endif
#if !defined(PFNGLOBJECTLABELPROC)
typedef void(*PFNGLOBJECTLABELPROC)(GLenum,GLuint,GLsizei,const GLchar*);
#endif
#if !defined(PFNGLOBJECTPTRLABELPROC)
typedef void(*PFNGLOBJECTPTRLABELPROC)(const void*,GLsizei,const GLchar*);
#endif
#if !defined(PFNGLORTHOFOESPROC)
typedef void(*PFNGLORTHOFOESPROC)(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLORTHOPROC)
typedef void(*PFNGLORTHOPROC)(GLdouble,GLdouble,GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLORTHOXOESPROC)
typedef void(*PFNGLORTHOXOESPROC)(GLfixed,GLfixed,GLfixed,GLfixed,GLfixed,GLfixed);
#endif
#if !defined(PFNGLPASSTEXCOORDATIPROC)
typedef void(*PFNGLPASSTEXCOORDATIPROC)(GLuint,GLuint,GLenum);
#endif
#if !defined(PFNGLPASSTHROUGHPROC)
typedef void(*PFNGLPASSTHROUGHPROC)(GLfloat);
#endif
#if !defined(PFNGLPASSTHROUGHXOESPROC)
typedef void(*PFNGLPASSTHROUGHXOESPROC)(GLfixed);
#endif
#if !defined(PFNGLPATCHPARAMETERFVPROC)
typedef void(*PFNGLPATCHPARAMETERFVPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLPATCHPARAMETERIPROC)
typedef void(*PFNGLPATCHPARAMETERIPROC)(GLenum,GLint);
#endif
#if !defined(PFNGLPATHCOLORGENNVPROC)
typedef void(*PFNGLPATHCOLORGENNVPROC)(GLenum,GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLPATHCOMMANDSNVPROC)
typedef void(*PFNGLPATHCOMMANDSNVPROC)(GLuint,GLsizei,const GLubyte*,GLsizei,GLenum,const void*);
#endif
#if !defined(PFNGLPATHCOORDSNVPROC)
typedef void(*PFNGLPATHCOORDSNVPROC)(GLuint,GLsizei,GLenum,const void*);
#endif
#if !defined(PFNGLPATHCOVERDEPTHFUNCNVPROC)
typedef void(*PFNGLPATHCOVERDEPTHFUNCNVPROC)(GLenum);
#endif
#if !defined(PFNGLPATHDASHARRAYNVPROC)
typedef void(*PFNGLPATHDASHARRAYNVPROC)(GLuint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLPATHFOGGENNVPROC)
typedef void(*PFNGLPATHFOGGENNVPROC)(GLenum);
#endif
#if !defined(PFNGLPATHGLYPHRANGENVPROC)
typedef void(*PFNGLPATHGLYPHRANGENVPROC)(GLuint,GLenum,const void*,GLbitfield,GLuint,GLsizei,GLenum,GLuint,GLfloat);
#endif
#if !defined(PFNGLPATHGLYPHSNVPROC)
typedef void(*PFNGLPATHGLYPHSNVPROC)(GLuint,GLenum,const void*,GLbitfield,GLsizei,GLenum,const void*,GLenum,GLuint,GLfloat);
#endif
#if !defined(PFNGLPATHPARAMETERFNVPROC)
typedef void(*PFNGLPATHPARAMETERFNVPROC)(GLuint,GLenum,GLfloat);
#endif
#if !defined(PFNGLPATHPARAMETERFVNVPROC)
typedef void(*PFNGLPATHPARAMETERFVNVPROC)(GLuint,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLPATHPARAMETERINVPROC)
typedef void(*PFNGLPATHPARAMETERINVPROC)(GLuint,GLenum,GLint);
#endif
#if !defined(PFNGLPATHPARAMETERIVNVPROC)
typedef void(*PFNGLPATHPARAMETERIVNVPROC)(GLuint,GLenum,const GLint*);
#endif
#if !defined(PFNGLPATHSTENCILDEPTHOFFSETNVPROC)
typedef void(*PFNGLPATHSTENCILDEPTHOFFSETNVPROC)(GLfloat,GLfloat);
#endif
#if !defined(PFNGLPATHSTENCILFUNCNVPROC)
typedef void(*PFNGLPATHSTENCILFUNCNVPROC)(GLenum,GLint,GLuint);
#endif
#if !defined(PFNGLPATHSTRINGNVPROC)
typedef void(*PFNGLPATHSTRINGNVPROC)(GLuint,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLPATHSUBCOMMANDSNVPROC)
typedef void(*PFNGLPATHSUBCOMMANDSNVPROC)(GLuint,GLsizei,GLsizei,GLsizei,const GLubyte*,GLsizei,GLenum,const void*);
#endif
#if !defined(PFNGLPATHSUBCOORDSNVPROC)
typedef void(*PFNGLPATHSUBCOORDSNVPROC)(GLuint,GLsizei,GLsizei,GLenum,const void*);
#endif
#if !defined(PFNGLPATHTEXGENNVPROC)
typedef void(*PFNGLPATHTEXGENNVPROC)(GLenum,GLenum,GLint,const GLfloat*);
#endif
#if !defined(PFNGLPAUSETRANSFORMFEEDBACKPROC)
typedef void(*PFNGLPAUSETRANSFORMFEEDBACKPROC)();
#endif
#if !defined(PFNGLPAUSETRANSFORMFEEDBACKNVPROC)
typedef void(*PFNGLPAUSETRANSFORMFEEDBACKNVPROC)();
#endif
#if !defined(PFNGLPIXELDATARANGENVPROC)
typedef void(*PFNGLPIXELDATARANGENVPROC)(GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLPIXELMAPFVPROC)
typedef void(*PFNGLPIXELMAPFVPROC)(GLenum,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLPIXELMAPUIVPROC)
typedef void(*PFNGLPIXELMAPUIVPROC)(GLenum,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLPIXELMAPUSVPROC)
typedef void(*PFNGLPIXELMAPUSVPROC)(GLenum,GLsizei,const GLushort*);
#endif
#if !defined(PFNGLPIXELMAPXPROC)
typedef void(*PFNGLPIXELMAPXPROC)(GLenum,GLint,const GLfixed*);
#endif
#if !defined(PFNGLPIXELSTOREFPROC)
typedef void(*PFNGLPIXELSTOREFPROC)(GLenum,GLfloat);
#endif
#if !defined(PFNGLPIXELSTOREIPROC)
typedef void(*PFNGLPIXELSTOREIPROC)(GLenum,GLint);
#endif
#if !defined(PFNGLPIXELSTOREXPROC)
typedef void(*PFNGLPIXELSTOREXPROC)(GLenum,GLfixed);
#endif
#if !defined(PFNGLPIXELTEXGENPARAMETERFSGISPROC)
typedef void(*PFNGLPIXELTEXGENPARAMETERFSGISPROC)(GLenum,GLfloat);
#endif
#if !defined(PFNGLPIXELTEXGENPARAMETERFVSGISPROC)
typedef void(*PFNGLPIXELTEXGENPARAMETERFVSGISPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLPIXELTEXGENPARAMETERISGISPROC)
typedef void(*PFNGLPIXELTEXGENPARAMETERISGISPROC)(GLenum,GLint);
#endif
#if !defined(PFNGLPIXELTEXGENPARAMETERIVSGISPROC)
typedef void(*PFNGLPIXELTEXGENPARAMETERIVSGISPROC)(GLenum,const GLint*);
#endif
#if !defined(PFNGLPIXELTEXGENSGIXPROC)
typedef void(*PFNGLPIXELTEXGENSGIXPROC)(GLenum);
#endif
#if !defined(PFNGLPIXELTRANSFERFPROC)
typedef void(*PFNGLPIXELTRANSFERFPROC)(GLenum,GLfloat);
#endif
#if !defined(PFNGLPIXELTRANSFERIPROC)
typedef void(*PFNGLPIXELTRANSFERIPROC)(GLenum,GLint);
#endif
#if !defined(PFNGLPIXELTRANSFERXOESPROC)
typedef void(*PFNGLPIXELTRANSFERXOESPROC)(GLenum,GLfixed);
#endif
#if !defined(PFNGLPIXELTRANSFORMPARAMETERFEXTPROC)
typedef void(*PFNGLPIXELTRANSFORMPARAMETERFEXTPROC)(GLenum,GLenum,GLfloat);
#endif
#if !defined(PFNGLPIXELTRANSFORMPARAMETERFVEXTPROC)
typedef void(*PFNGLPIXELTRANSFORMPARAMETERFVEXTPROC)(GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLPIXELTRANSFORMPARAMETERIEXTPROC)
typedef void(*PFNGLPIXELTRANSFORMPARAMETERIEXTPROC)(GLenum,GLenum,GLint);
#endif
#if !defined(PFNGLPIXELTRANSFORMPARAMETERIVEXTPROC)
typedef void(*PFNGLPIXELTRANSFORMPARAMETERIVEXTPROC)(GLenum,GLenum,const GLint*);
#endif
#if !defined(PFNGLPIXELZOOMPROC)
typedef void(*PFNGLPIXELZOOMPROC)(GLfloat,GLfloat);
#endif
#if !defined(PFNGLPIXELZOOMXOESPROC)
typedef void(*PFNGLPIXELZOOMXOESPROC)(GLfixed,GLfixed);
#endif
#if !defined(PFNGLPNTRIANGLESFATIPROC)
typedef void(*PFNGLPNTRIANGLESFATIPROC)(GLenum,GLfloat);
#endif
#if !defined(PFNGLPNTRIANGLESIATIPROC)
typedef void(*PFNGLPNTRIANGLESIATIPROC)(GLenum,GLint);
#endif
#if !defined(PFNGLPOINTPARAMETERFARBPROC)
typedef void(*PFNGLPOINTPARAMETERFARBPROC)(GLenum,GLfloat);
#endif
#if !defined(PFNGLPOINTPARAMETERFEXTPROC)
typedef void(*PFNGLPOINTPARAMETERFEXTPROC)(GLenum,GLfloat);
#endif
#if !defined(PFNGLPOINTPARAMETERFPROC)
typedef void(*PFNGLPOINTPARAMETERFPROC)(GLenum,GLfloat);
#endif
#if !defined(PFNGLPOINTPARAMETERFSGISPROC)
typedef void(*PFNGLPOINTPARAMETERFSGISPROC)(GLenum,GLfloat);
#endif
#if !defined(PFNGLPOINTPARAMETERFVARBPROC)
typedef void(*PFNGLPOINTPARAMETERFVARBPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLPOINTPARAMETERFVEXTPROC)
typedef void(*PFNGLPOINTPARAMETERFVEXTPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLPOINTPARAMETERFVPROC)
typedef void(*PFNGLPOINTPARAMETERFVPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLPOINTPARAMETERFVSGISPROC)
typedef void(*PFNGLPOINTPARAMETERFVSGISPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLPOINTPARAMETERIPROC)
typedef void(*PFNGLPOINTPARAMETERIPROC)(GLenum,GLint);
#endif
#if !defined(PFNGLPOINTPARAMETERINVPROC)
typedef void(*PFNGLPOINTPARAMETERINVPROC)(GLenum,GLint);
#endif
#if !defined(PFNGLPOINTPARAMETERIVPROC)
typedef void(*PFNGLPOINTPARAMETERIVPROC)(GLenum,const GLint*);
#endif
#if !defined(PFNGLPOINTPARAMETERIVNVPROC)
typedef void(*PFNGLPOINTPARAMETERIVNVPROC)(GLenum,const GLint*);
#endif
#if !defined(PFNGLPOINTPARAMETERXVOESPROC)
typedef void(*PFNGLPOINTPARAMETERXVOESPROC)(GLenum,const GLfixed*);
#endif
#if !defined(PFNGLPOINTSIZEPROC)
typedef void(*PFNGLPOINTSIZEPROC)(GLfloat);
#endif
#if !defined(PFNGLPOINTSIZEXOESPROC)
typedef void(*PFNGLPOINTSIZEXOESPROC)(GLfixed);
#endif
#if !defined(PFNGLPOLYGONMODEPROC)
typedef void(*PFNGLPOLYGONMODEPROC)(GLenum,GLenum);
#endif
#if !defined(PFNGLPOLYGONOFFSETCLAMPEXTPROC)
typedef void(*PFNGLPOLYGONOFFSETCLAMPEXTPROC)(GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLPOLYGONOFFSETEXTPROC)
typedef void(*PFNGLPOLYGONOFFSETEXTPROC)(GLfloat,GLfloat);
#endif
#if !defined(PFNGLPOLYGONOFFSETPROC)
typedef void(*PFNGLPOLYGONOFFSETPROC)(GLfloat,GLfloat);
#endif
#if !defined(PFNGLPOLYGONOFFSETXOESPROC)
typedef void(*PFNGLPOLYGONOFFSETXOESPROC)(GLfixed,GLfixed);
#endif
#if !defined(PFNGLPOLYGONSTIPPLEPROC)
typedef void(*PFNGLPOLYGONSTIPPLEPROC)(const GLubyte*);
#endif
#if !defined(PFNGLPOPATTRIBPROC)
typedef void(*PFNGLPOPATTRIBPROC)();
#endif
#if !defined(PFNGLPOPCLIENTATTRIBPROC)
typedef void(*PFNGLPOPCLIENTATTRIBPROC)();
#endif
#if !defined(PFNGLPOPDEBUGGROUPPROC)
typedef void(*PFNGLPOPDEBUGGROUPPROC)();
#endif
#if !defined(PFNGLPOPGROUPMARKEREXTPROC)
typedef void(*PFNGLPOPGROUPMARKEREXTPROC)();
#endif
#if !defined(PFNGLPOPMATRIXPROC)
typedef void(*PFNGLPOPMATRIXPROC)();
#endif
#if !defined(PFNGLPOPNAMEPROC)
typedef void(*PFNGLPOPNAMEPROC)();
#endif
#if !defined(PFNGLPRESENTFRAMEDUALFILLNVPROC)
typedef void(*PFNGLPRESENTFRAMEDUALFILLNVPROC)(GLuint,GLuint64EXT,GLuint,GLuint,GLenum,GLenum,GLuint,GLenum,GLuint,GLenum,GLuint,GLenum,GLuint);
#endif
#if !defined(PFNGLPRESENTFRAMEKEYEDNVPROC)
typedef void(*PFNGLPRESENTFRAMEKEYEDNVPROC)(GLuint,GLuint64EXT,GLuint,GLuint,GLenum,GLenum,GLuint,GLuint,GLenum,GLuint,GLuint);
#endif
#if !defined(PFNGLPRIMITIVEBOUNDINGBOXARBPROC)
typedef void(*PFNGLPRIMITIVEBOUNDINGBOXARBPROC)(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLPRIMITIVERESTARTINDEXPROC)
typedef void(*PFNGLPRIMITIVERESTARTINDEXPROC)(GLuint);
#endif
#if !defined(PFNGLPRIMITIVERESTARTINDEXNVPROC)
typedef void(*PFNGLPRIMITIVERESTARTINDEXNVPROC)(GLuint);
#endif
#if !defined(PFNGLPRIMITIVERESTARTNVPROC)
typedef void(*PFNGLPRIMITIVERESTARTNVPROC)();
#endif
#if !defined(PFNGLPRIORITIZETEXTURESEXTPROC)
typedef void(*PFNGLPRIORITIZETEXTURESEXTPROC)(GLsizei,const GLuint*,const GLclampf*);
#endif
#if !defined(PFNGLPRIORITIZETEXTURESPROC)
typedef void(*PFNGLPRIORITIZETEXTURESPROC)(GLsizei,const GLuint*,const GLclampf*);
#endif
#if !defined(PFNGLPRIORITIZETEXTURESXOESPROC)
typedef void(*PFNGLPRIORITIZETEXTURESXOESPROC)(GLsizei,const GLuint*,const GLfixed*);
#endif
#if !defined(PFNGLPROGRAMBINARYPROC)
typedef void(*PFNGLPROGRAMBINARYPROC)(GLuint,GLenum,const void*,GLsizei);
#endif
#if !defined(PFNGLPROGRAMBUFFERPARAMETERSFVNVPROC)
typedef void(*PFNGLPROGRAMBUFFERPARAMETERSFVNVPROC)(GLenum,GLuint,GLuint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMBUFFERPARAMETERSIIVNVPROC)
typedef void(*PFNGLPROGRAMBUFFERPARAMETERSIIVNVPROC)(GLenum,GLuint,GLuint,GLsizei,const GLint*);
#endif
#if !defined(PFNGLPROGRAMBUFFERPARAMETERSIUIVNVPROC)
typedef void(*PFNGLPROGRAMBUFFERPARAMETERSIUIVNVPROC)(GLenum,GLuint,GLuint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLPROGRAMENVPARAMETER4DARBPROC)
typedef void(*PFNGLPROGRAMENVPARAMETER4DARBPROC)(GLenum,GLuint,GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLPROGRAMENVPARAMETER4DVARBPROC)
typedef void(*PFNGLPROGRAMENVPARAMETER4DVARBPROC)(GLenum,GLuint,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMENVPARAMETER4FARBPROC)
typedef void(*PFNGLPROGRAMENVPARAMETER4FARBPROC)(GLenum,GLuint,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLPROGRAMENVPARAMETER4FVARBPROC)
typedef void(*PFNGLPROGRAMENVPARAMETER4FVARBPROC)(GLenum,GLuint,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMENVPARAMETERI4INVPROC)
typedef void(*PFNGLPROGRAMENVPARAMETERI4INVPROC)(GLenum,GLuint,GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLPROGRAMENVPARAMETERI4IVNVPROC)
typedef void(*PFNGLPROGRAMENVPARAMETERI4IVNVPROC)(GLenum,GLuint,const GLint*);
#endif
#if !defined(PFNGLPROGRAMENVPARAMETERI4UINVPROC)
typedef void(*PFNGLPROGRAMENVPARAMETERI4UINVPROC)(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLPROGRAMENVPARAMETERI4UIVNVPROC)
typedef void(*PFNGLPROGRAMENVPARAMETERI4UIVNVPROC)(GLenum,GLuint,const GLuint*);
#endif
#if !defined(PFNGLPROGRAMENVPARAMETERS4FVEXTPROC)
typedef void(*PFNGLPROGRAMENVPARAMETERS4FVEXTPROC)(GLenum,GLuint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMENVPARAMETERSI4IVNVPROC)
typedef void(*PFNGLPROGRAMENVPARAMETERSI4IVNVPROC)(GLenum,GLuint,GLsizei,const GLint*);
#endif
#if !defined(PFNGLPROGRAMENVPARAMETERSI4UIVNVPROC)
typedef void(*PFNGLPROGRAMENVPARAMETERSI4UIVNVPROC)(GLenum,GLuint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLPROGRAMLOCALPARAMETER4DARBPROC)
typedef void(*PFNGLPROGRAMLOCALPARAMETER4DARBPROC)(GLenum,GLuint,GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLPROGRAMLOCALPARAMETER4DVARBPROC)
typedef void(*PFNGLPROGRAMLOCALPARAMETER4DVARBPROC)(GLenum,GLuint,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMLOCALPARAMETER4FARBPROC)
typedef void(*PFNGLPROGRAMLOCALPARAMETER4FARBPROC)(GLenum,GLuint,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLPROGRAMLOCALPARAMETER4FVARBPROC)
typedef void(*PFNGLPROGRAMLOCALPARAMETER4FVARBPROC)(GLenum,GLuint,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMLOCALPARAMETERI4INVPROC)
typedef void(*PFNGLPROGRAMLOCALPARAMETERI4INVPROC)(GLenum,GLuint,GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLPROGRAMLOCALPARAMETERI4IVNVPROC)
typedef void(*PFNGLPROGRAMLOCALPARAMETERI4IVNVPROC)(GLenum,GLuint,const GLint*);
#endif
#if !defined(PFNGLPROGRAMLOCALPARAMETERI4UINVPROC)
typedef void(*PFNGLPROGRAMLOCALPARAMETERI4UINVPROC)(GLenum,GLuint,GLuint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLPROGRAMLOCALPARAMETERI4UIVNVPROC)
typedef void(*PFNGLPROGRAMLOCALPARAMETERI4UIVNVPROC)(GLenum,GLuint,const GLuint*);
#endif
#if !defined(PFNGLPROGRAMLOCALPARAMETERS4FVEXTPROC)
typedef void(*PFNGLPROGRAMLOCALPARAMETERS4FVEXTPROC)(GLenum,GLuint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMLOCALPARAMETERSI4IVNVPROC)
typedef void(*PFNGLPROGRAMLOCALPARAMETERSI4IVNVPROC)(GLenum,GLuint,GLsizei,const GLint*);
#endif
#if !defined(PFNGLPROGRAMLOCALPARAMETERSI4UIVNVPROC)
typedef void(*PFNGLPROGRAMLOCALPARAMETERSI4UIVNVPROC)(GLenum,GLuint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLPROGRAMNAMEDPARAMETER4DNVPROC)
typedef void(*PFNGLPROGRAMNAMEDPARAMETER4DNVPROC)(GLuint,GLsizei,const GLubyte*,GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLPROGRAMNAMEDPARAMETER4DVNVPROC)
typedef void(*PFNGLPROGRAMNAMEDPARAMETER4DVNVPROC)(GLuint,GLsizei,const GLubyte*,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMNAMEDPARAMETER4FNVPROC)
typedef void(*PFNGLPROGRAMNAMEDPARAMETER4FNVPROC)(GLuint,GLsizei,const GLubyte*,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLPROGRAMNAMEDPARAMETER4FVNVPROC)
typedef void(*PFNGLPROGRAMNAMEDPARAMETER4FVNVPROC)(GLuint,GLsizei,const GLubyte*,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMPARAMETER4DNVPROC)
typedef void(*PFNGLPROGRAMPARAMETER4DNVPROC)(GLenum,GLuint,GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLPROGRAMPARAMETER4DVNVPROC)
typedef void(*PFNGLPROGRAMPARAMETER4DVNVPROC)(GLenum,GLuint,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMPARAMETER4FNVPROC)
typedef void(*PFNGLPROGRAMPARAMETER4FNVPROC)(GLenum,GLuint,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLPROGRAMPARAMETER4FVNVPROC)
typedef void(*PFNGLPROGRAMPARAMETER4FVNVPROC)(GLenum,GLuint,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMPARAMETERIARBPROC)
typedef void(*PFNGLPROGRAMPARAMETERIARBPROC)(GLuint,GLenum,GLint);
#endif
#if !defined(PFNGLPROGRAMPARAMETERIEXTPROC)
typedef void(*PFNGLPROGRAMPARAMETERIEXTPROC)(GLuint,GLenum,GLint);
#endif
#if !defined(PFNGLPROGRAMPARAMETERIPROC)
typedef void(*PFNGLPROGRAMPARAMETERIPROC)(GLuint,GLenum,GLint);
#endif
#if !defined(PFNGLPROGRAMPARAMETERS4DVNVPROC)
typedef void(*PFNGLPROGRAMPARAMETERS4DVNVPROC)(GLenum,GLuint,GLsizei,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMPARAMETERS4FVNVPROC)
typedef void(*PFNGLPROGRAMPARAMETERS4FVNVPROC)(GLenum,GLuint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC)
typedef void(*PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC)(GLuint,GLint,GLenum,GLint,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMSTRINGARBPROC)
typedef void(*PFNGLPROGRAMSTRINGARBPROC)(GLenum,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLPROGRAMSUBROUTINEPARAMETERSUIVNVPROC)
typedef void(*PFNGLPROGRAMSUBROUTINEPARAMETERSUIVNVPROC)(GLenum,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1DEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM1DEXTPROC)(GLuint,GLint,GLdouble);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1DPROC)
typedef void(*PFNGLPROGRAMUNIFORM1DPROC)(GLuint,GLint,GLdouble);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1DVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM1DVEXTPROC)(GLuint,GLint,GLsizei,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1DVPROC)
typedef void(*PFNGLPROGRAMUNIFORM1DVPROC)(GLuint,GLint,GLsizei,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1FEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM1FEXTPROC)(GLuint,GLint,GLfloat);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1FPROC)
typedef void(*PFNGLPROGRAMUNIFORM1FPROC)(GLuint,GLint,GLfloat);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1FVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM1FVEXTPROC)(GLuint,GLint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1FVPROC)
typedef void(*PFNGLPROGRAMUNIFORM1FVPROC)(GLuint,GLint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1I64ARBPROC)
typedef void(*PFNGLPROGRAMUNIFORM1I64ARBPROC)(GLuint,GLint,GLint64);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1I64NVPROC)
typedef void(*PFNGLPROGRAMUNIFORM1I64NVPROC)(GLuint,GLint,GLint64EXT);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1I64VARBPROC)
typedef void(*PFNGLPROGRAMUNIFORM1I64VARBPROC)(GLuint,GLint,GLsizei,const GLint64*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1I64VNVPROC)
typedef void(*PFNGLPROGRAMUNIFORM1I64VNVPROC)(GLuint,GLint,GLsizei,const GLint64EXT*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1IEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM1IEXTPROC)(GLuint,GLint,GLint);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1IPROC)
typedef void(*PFNGLPROGRAMUNIFORM1IPROC)(GLuint,GLint,GLint);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1IVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM1IVEXTPROC)(GLuint,GLint,GLsizei,const GLint*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1IVPROC)
typedef void(*PFNGLPROGRAMUNIFORM1IVPROC)(GLuint,GLint,GLsizei,const GLint*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1UI64ARBPROC)
typedef void(*PFNGLPROGRAMUNIFORM1UI64ARBPROC)(GLuint,GLint,GLuint64);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1UI64NVPROC)
typedef void(*PFNGLPROGRAMUNIFORM1UI64NVPROC)(GLuint,GLint,GLuint64EXT);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1UI64VARBPROC)
typedef void(*PFNGLPROGRAMUNIFORM1UI64VARBPROC)(GLuint,GLint,GLsizei,const GLuint64*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1UI64VNVPROC)
typedef void(*PFNGLPROGRAMUNIFORM1UI64VNVPROC)(GLuint,GLint,GLsizei,const GLuint64EXT*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1UIEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM1UIEXTPROC)(GLuint,GLint,GLuint);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1UIPROC)
typedef void(*PFNGLPROGRAMUNIFORM1UIPROC)(GLuint,GLint,GLuint);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1UIVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM1UIVEXTPROC)(GLuint,GLint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM1UIVPROC)
typedef void(*PFNGLPROGRAMUNIFORM1UIVPROC)(GLuint,GLint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2DEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM2DEXTPROC)(GLuint,GLint,GLdouble,GLdouble);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2DPROC)
typedef void(*PFNGLPROGRAMUNIFORM2DPROC)(GLuint,GLint,GLdouble,GLdouble);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2DVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM2DVEXTPROC)(GLuint,GLint,GLsizei,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2DVPROC)
typedef void(*PFNGLPROGRAMUNIFORM2DVPROC)(GLuint,GLint,GLsizei,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2FEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM2FEXTPROC)(GLuint,GLint,GLfloat,GLfloat);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2FPROC)
typedef void(*PFNGLPROGRAMUNIFORM2FPROC)(GLuint,GLint,GLfloat,GLfloat);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2FVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM2FVEXTPROC)(GLuint,GLint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2FVPROC)
typedef void(*PFNGLPROGRAMUNIFORM2FVPROC)(GLuint,GLint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2I64ARBPROC)
typedef void(*PFNGLPROGRAMUNIFORM2I64ARBPROC)(GLuint,GLint,GLint64,GLint64);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2I64NVPROC)
typedef void(*PFNGLPROGRAMUNIFORM2I64NVPROC)(GLuint,GLint,GLint64EXT,GLint64EXT);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2I64VARBPROC)
typedef void(*PFNGLPROGRAMUNIFORM2I64VARBPROC)(GLuint,GLint,GLsizei,const GLint64*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2I64VNVPROC)
typedef void(*PFNGLPROGRAMUNIFORM2I64VNVPROC)(GLuint,GLint,GLsizei,const GLint64EXT*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2IEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM2IEXTPROC)(GLuint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2IPROC)
typedef void(*PFNGLPROGRAMUNIFORM2IPROC)(GLuint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2IVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM2IVEXTPROC)(GLuint,GLint,GLsizei,const GLint*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2IVPROC)
typedef void(*PFNGLPROGRAMUNIFORM2IVPROC)(GLuint,GLint,GLsizei,const GLint*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2UI64ARBPROC)
typedef void(*PFNGLPROGRAMUNIFORM2UI64ARBPROC)(GLuint,GLint,GLuint64,GLuint64);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2UI64NVPROC)
typedef void(*PFNGLPROGRAMUNIFORM2UI64NVPROC)(GLuint,GLint,GLuint64EXT,GLuint64EXT);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2UI64VARBPROC)
typedef void(*PFNGLPROGRAMUNIFORM2UI64VARBPROC)(GLuint,GLint,GLsizei,const GLuint64*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2UI64VNVPROC)
typedef void(*PFNGLPROGRAMUNIFORM2UI64VNVPROC)(GLuint,GLint,GLsizei,const GLuint64EXT*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2UIEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM2UIEXTPROC)(GLuint,GLint,GLuint,GLuint);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2UIPROC)
typedef void(*PFNGLPROGRAMUNIFORM2UIPROC)(GLuint,GLint,GLuint,GLuint);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2UIVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM2UIVEXTPROC)(GLuint,GLint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM2UIVPROC)
typedef void(*PFNGLPROGRAMUNIFORM2UIVPROC)(GLuint,GLint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3DEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM3DEXTPROC)(GLuint,GLint,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3DPROC)
typedef void(*PFNGLPROGRAMUNIFORM3DPROC)(GLuint,GLint,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3DVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM3DVEXTPROC)(GLuint,GLint,GLsizei,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3DVPROC)
typedef void(*PFNGLPROGRAMUNIFORM3DVPROC)(GLuint,GLint,GLsizei,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3FEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM3FEXTPROC)(GLuint,GLint,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3FPROC)
typedef void(*PFNGLPROGRAMUNIFORM3FPROC)(GLuint,GLint,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3FVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM3FVEXTPROC)(GLuint,GLint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3FVPROC)
typedef void(*PFNGLPROGRAMUNIFORM3FVPROC)(GLuint,GLint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3I64ARBPROC)
typedef void(*PFNGLPROGRAMUNIFORM3I64ARBPROC)(GLuint,GLint,GLint64,GLint64,GLint64);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3I64NVPROC)
typedef void(*PFNGLPROGRAMUNIFORM3I64NVPROC)(GLuint,GLint,GLint64EXT,GLint64EXT,GLint64EXT);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3I64VARBPROC)
typedef void(*PFNGLPROGRAMUNIFORM3I64VARBPROC)(GLuint,GLint,GLsizei,const GLint64*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3I64VNVPROC)
typedef void(*PFNGLPROGRAMUNIFORM3I64VNVPROC)(GLuint,GLint,GLsizei,const GLint64EXT*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3IEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM3IEXTPROC)(GLuint,GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3IPROC)
typedef void(*PFNGLPROGRAMUNIFORM3IPROC)(GLuint,GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3IVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM3IVEXTPROC)(GLuint,GLint,GLsizei,const GLint*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3IVPROC)
typedef void(*PFNGLPROGRAMUNIFORM3IVPROC)(GLuint,GLint,GLsizei,const GLint*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3UI64ARBPROC)
typedef void(*PFNGLPROGRAMUNIFORM3UI64ARBPROC)(GLuint,GLint,GLuint64,GLuint64,GLuint64);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3UI64NVPROC)
typedef void(*PFNGLPROGRAMUNIFORM3UI64NVPROC)(GLuint,GLint,GLuint64EXT,GLuint64EXT,GLuint64EXT);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3UI64VARBPROC)
typedef void(*PFNGLPROGRAMUNIFORM3UI64VARBPROC)(GLuint,GLint,GLsizei,const GLuint64*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3UI64VNVPROC)
typedef void(*PFNGLPROGRAMUNIFORM3UI64VNVPROC)(GLuint,GLint,GLsizei,const GLuint64EXT*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3UIEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM3UIEXTPROC)(GLuint,GLint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3UIPROC)
typedef void(*PFNGLPROGRAMUNIFORM3UIPROC)(GLuint,GLint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3UIVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM3UIVEXTPROC)(GLuint,GLint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM3UIVPROC)
typedef void(*PFNGLPROGRAMUNIFORM3UIVPROC)(GLuint,GLint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4DEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM4DEXTPROC)(GLuint,GLint,GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4DPROC)
typedef void(*PFNGLPROGRAMUNIFORM4DPROC)(GLuint,GLint,GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4DVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM4DVEXTPROC)(GLuint,GLint,GLsizei,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4DVPROC)
typedef void(*PFNGLPROGRAMUNIFORM4DVPROC)(GLuint,GLint,GLsizei,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4FEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM4FEXTPROC)(GLuint,GLint,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4FPROC)
typedef void(*PFNGLPROGRAMUNIFORM4FPROC)(GLuint,GLint,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4FVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM4FVEXTPROC)(GLuint,GLint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4FVPROC)
typedef void(*PFNGLPROGRAMUNIFORM4FVPROC)(GLuint,GLint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4I64ARBPROC)
typedef void(*PFNGLPROGRAMUNIFORM4I64ARBPROC)(GLuint,GLint,GLint64,GLint64,GLint64,GLint64);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4I64NVPROC)
typedef void(*PFNGLPROGRAMUNIFORM4I64NVPROC)(GLuint,GLint,GLint64EXT,GLint64EXT,GLint64EXT,GLint64EXT);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4I64VARBPROC)
typedef void(*PFNGLPROGRAMUNIFORM4I64VARBPROC)(GLuint,GLint,GLsizei,const GLint64*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4I64VNVPROC)
typedef void(*PFNGLPROGRAMUNIFORM4I64VNVPROC)(GLuint,GLint,GLsizei,const GLint64EXT*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4IEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM4IEXTPROC)(GLuint,GLint,GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4IPROC)
typedef void(*PFNGLPROGRAMUNIFORM4IPROC)(GLuint,GLint,GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4IVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM4IVEXTPROC)(GLuint,GLint,GLsizei,const GLint*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4IVPROC)
typedef void(*PFNGLPROGRAMUNIFORM4IVPROC)(GLuint,GLint,GLsizei,const GLint*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4UI64ARBPROC)
typedef void(*PFNGLPROGRAMUNIFORM4UI64ARBPROC)(GLuint,GLint,GLuint64,GLuint64,GLuint64,GLuint64);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4UI64NVPROC)
typedef void(*PFNGLPROGRAMUNIFORM4UI64NVPROC)(GLuint,GLint,GLuint64EXT,GLuint64EXT,GLuint64EXT,GLuint64EXT);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4UI64VARBPROC)
typedef void(*PFNGLPROGRAMUNIFORM4UI64VARBPROC)(GLuint,GLint,GLsizei,const GLuint64*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4UI64VNVPROC)
typedef void(*PFNGLPROGRAMUNIFORM4UI64VNVPROC)(GLuint,GLint,GLsizei,const GLuint64EXT*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4UIEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM4UIEXTPROC)(GLuint,GLint,GLuint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4UIPROC)
typedef void(*PFNGLPROGRAMUNIFORM4UIPROC)(GLuint,GLint,GLuint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4UIVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORM4UIVEXTPROC)(GLuint,GLint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLPROGRAMUNIFORM4UIVPROC)
typedef void(*PFNGLPROGRAMUNIFORM4UIVPROC)(GLuint,GLint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC)
typedef void(*PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC)(GLuint,GLint,GLuint64);
#endif
#if !defined(PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC)
typedef void(*PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC)(GLuint,GLint,GLuint64);
#endif
#if !defined(PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC)
typedef void(*PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC)(GLuint,GLint,GLsizei,const GLuint64*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC)
typedef void(*PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC)(GLuint,GLint,GLsizei,const GLuint64*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX2DVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX2DVEXTPROC)(GLuint,GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX2DVPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX2DVPROC)(GLuint,GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC)(GLuint,GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX2FVPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX2FVPROC)(GLuint,GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX2X3DVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX2X3DVEXTPROC)(GLuint,GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC)(GLuint,GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC)(GLuint,GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)(GLuint,GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX2X4DVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX2X4DVEXTPROC)(GLuint,GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC)(GLuint,GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC)(GLuint,GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)(GLuint,GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX3DVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX3DVEXTPROC)(GLuint,GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX3DVPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX3DVPROC)(GLuint,GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC)(GLuint,GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX3FVPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX3FVPROC)(GLuint,GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX3X2DVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX3X2DVEXTPROC)(GLuint,GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC)(GLuint,GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC)(GLuint,GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)(GLuint,GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX3X4DVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX3X4DVEXTPROC)(GLuint,GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC)(GLuint,GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC)(GLuint,GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)(GLuint,GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX4DVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX4DVEXTPROC)(GLuint,GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX4DVPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX4DVPROC)(GLuint,GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC)(GLuint,GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX4FVPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX4FVPROC)(GLuint,GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX4X2DVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX4X2DVEXTPROC)(GLuint,GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC)(GLuint,GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC)(GLuint,GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)(GLuint,GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX4X3DVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX4X3DVEXTPROC)(GLuint,GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC)(GLuint,GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC)(GLuint,GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)
typedef void(*PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)(GLuint,GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLPROGRAMUNIFORMUI64NVPROC)
typedef void(*PFNGLPROGRAMUNIFORMUI64NVPROC)(GLuint,GLint,GLuint64EXT);
#endif
#if !defined(PFNGLPROGRAMUNIFORMUI64VNVPROC)
typedef void(*PFNGLPROGRAMUNIFORMUI64VNVPROC)(GLuint,GLint,GLsizei,const GLuint64EXT*);
#endif
#if !defined(PFNGLPROGRAMVERTEXLIMITNVPROC)
typedef void(*PFNGLPROGRAMVERTEXLIMITNVPROC)(GLenum,GLint);
#endif
#if !defined(PFNGLPROVOKINGVERTEXEXTPROC)
typedef void(*PFNGLPROVOKINGVERTEXEXTPROC)(GLenum);
#endif
#if !defined(PFNGLPROVOKINGVERTEXPROC)
typedef void(*PFNGLPROVOKINGVERTEXPROC)(GLenum);
#endif
#if !defined(PFNGLPUSHATTRIBPROC)
typedef void(*PFNGLPUSHATTRIBPROC)(GLbitfield);
#endif
#if !defined(PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC)
typedef void(*PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC)(GLbitfield);
#endif
#if !defined(PFNGLPUSHCLIENTATTRIBPROC)
typedef void(*PFNGLPUSHCLIENTATTRIBPROC)(GLbitfield);
#endif
#if !defined(PFNGLPUSHDEBUGGROUPPROC)
typedef void(*PFNGLPUSHDEBUGGROUPPROC)(GLenum,GLuint,GLsizei,const GLchar*);
#endif
#if !defined(PFNGLPUSHGROUPMARKEREXTPROC)
typedef void(*PFNGLPUSHGROUPMARKEREXTPROC)(GLsizei,const GLchar*);
#endif
#if !defined(PFNGLPUSHMATRIXPROC)
typedef void(*PFNGLPUSHMATRIXPROC)();
#endif
#if !defined(PFNGLPUSHNAMEPROC)
typedef void(*PFNGLPUSHNAMEPROC)(GLuint);
#endif
#if !defined(PFNGLQUERYCOUNTERPROC)
typedef void(*PFNGLQUERYCOUNTERPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLQUERYOBJECTPARAMETERUIAMDPROC)
typedef void(*PFNGLQUERYOBJECTPARAMETERUIAMDPROC)(GLenum,GLuint,GLenum,GLuint);
#endif
#if !defined(PFNGLRASTERPOS2DPROC)
typedef void(*PFNGLRASTERPOS2DPROC)(GLdouble,GLdouble);
#endif
#if !defined(PFNGLRASTERPOS2DVPROC)
typedef void(*PFNGLRASTERPOS2DVPROC)(const GLdouble*);
#endif
#if !defined(PFNGLRASTERPOS2FPROC)
typedef void(*PFNGLRASTERPOS2FPROC)(GLfloat,GLfloat);
#endif
#if !defined(PFNGLRASTERPOS2FVPROC)
typedef void(*PFNGLRASTERPOS2FVPROC)(const GLfloat*);
#endif
#if !defined(PFNGLRASTERPOS2IPROC)
typedef void(*PFNGLRASTERPOS2IPROC)(GLint,GLint);
#endif
#if !defined(PFNGLRASTERPOS2IVPROC)
typedef void(*PFNGLRASTERPOS2IVPROC)(const GLint*);
#endif
#if !defined(PFNGLRASTERPOS2SPROC)
typedef void(*PFNGLRASTERPOS2SPROC)(GLshort,GLshort);
#endif
#if !defined(PFNGLRASTERPOS2SVPROC)
typedef void(*PFNGLRASTERPOS2SVPROC)(const GLshort*);
#endif
#if !defined(PFNGLRASTERPOS2XOESPROC)
typedef void(*PFNGLRASTERPOS2XOESPROC)(GLfixed,GLfixed);
#endif
#if !defined(PFNGLRASTERPOS2XVOESPROC)
typedef void(*PFNGLRASTERPOS2XVOESPROC)(const GLfixed*);
#endif
#if !defined(PFNGLRASTERPOS3DPROC)
typedef void(*PFNGLRASTERPOS3DPROC)(GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLRASTERPOS3DVPROC)
typedef void(*PFNGLRASTERPOS3DVPROC)(const GLdouble*);
#endif
#if !defined(PFNGLRASTERPOS3FPROC)
typedef void(*PFNGLRASTERPOS3FPROC)(GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLRASTERPOS3FVPROC)
typedef void(*PFNGLRASTERPOS3FVPROC)(const GLfloat*);
#endif
#if !defined(PFNGLRASTERPOS3IPROC)
typedef void(*PFNGLRASTERPOS3IPROC)(GLint,GLint,GLint);
#endif
#if !defined(PFNGLRASTERPOS3IVPROC)
typedef void(*PFNGLRASTERPOS3IVPROC)(const GLint*);
#endif
#if !defined(PFNGLRASTERPOS3SPROC)
typedef void(*PFNGLRASTERPOS3SPROC)(GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLRASTERPOS3SVPROC)
typedef void(*PFNGLRASTERPOS3SVPROC)(const GLshort*);
#endif
#if !defined(PFNGLRASTERPOS3XOESPROC)
typedef void(*PFNGLRASTERPOS3XOESPROC)(GLfixed,GLfixed,GLfixed);
#endif
#if !defined(PFNGLRASTERPOS3XVOESPROC)
typedef void(*PFNGLRASTERPOS3XVOESPROC)(const GLfixed*);
#endif
#if !defined(PFNGLRASTERPOS4DPROC)
typedef void(*PFNGLRASTERPOS4DPROC)(GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLRASTERPOS4DVPROC)
typedef void(*PFNGLRASTERPOS4DVPROC)(const GLdouble*);
#endif
#if !defined(PFNGLRASTERPOS4FPROC)
typedef void(*PFNGLRASTERPOS4FPROC)(GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLRASTERPOS4FVPROC)
typedef void(*PFNGLRASTERPOS4FVPROC)(const GLfloat*);
#endif
#if !defined(PFNGLRASTERPOS4IPROC)
typedef void(*PFNGLRASTERPOS4IPROC)(GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLRASTERPOS4IVPROC)
typedef void(*PFNGLRASTERPOS4IVPROC)(const GLint*);
#endif
#if !defined(PFNGLRASTERPOS4SPROC)
typedef void(*PFNGLRASTERPOS4SPROC)(GLshort,GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLRASTERPOS4SVPROC)
typedef void(*PFNGLRASTERPOS4SVPROC)(const GLshort*);
#endif
#if !defined(PFNGLRASTERPOS4XOESPROC)
typedef void(*PFNGLRASTERPOS4XOESPROC)(GLfixed,GLfixed,GLfixed,GLfixed);
#endif
#if !defined(PFNGLRASTERPOS4XVOESPROC)
typedef void(*PFNGLRASTERPOS4XVOESPROC)(const GLfixed*);
#endif
#if !defined(PFNGLRASTERSAMPLESEXTPROC)
typedef void(*PFNGLRASTERSAMPLESEXTPROC)(GLuint,GLboolean);
#endif
#if !defined(PFNGLREADBUFFERPROC)
typedef void(*PFNGLREADBUFFERPROC)(GLenum);
#endif
#if !defined(PFNGLREADINSTRUMENTSSGIXPROC)
typedef void(*PFNGLREADINSTRUMENTSSGIXPROC)(GLint);
#endif
#if !defined(PFNGLREADNPIXELSARBPROC)
typedef void(*PFNGLREADNPIXELSARBPROC)(GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,GLsizei,void*);
#endif
#if !defined(PFNGLREADNPIXELSPROC)
typedef void(*PFNGLREADNPIXELSPROC)(GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,GLsizei,void*);
#endif
#if !defined(PFNGLREADPIXELSPROC)
typedef void(*PFNGLREADPIXELSPROC)(GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,GLvoid*);
#endif
#if !defined(PFNGLRECTDPROC)
typedef void(*PFNGLRECTDPROC)(GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLRECTDVPROC)
typedef void(*PFNGLRECTDVPROC)(const GLdouble*,const GLdouble*);
#endif
#if !defined(PFNGLRECTFPROC)
typedef void(*PFNGLRECTFPROC)(GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLRECTFVPROC)
typedef void(*PFNGLRECTFVPROC)(const GLfloat*,const GLfloat*);
#endif
#if !defined(PFNGLRECTIPROC)
typedef void(*PFNGLRECTIPROC)(GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLRECTIVPROC)
typedef void(*PFNGLRECTIVPROC)(const GLint*,const GLint*);
#endif
#if !defined(PFNGLRECTSPROC)
typedef void(*PFNGLRECTSPROC)(GLshort,GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLRECTSVPROC)
typedef void(*PFNGLRECTSVPROC)(const GLshort*,const GLshort*);
#endif
#if !defined(PFNGLRECTXOESPROC)
typedef void(*PFNGLRECTXOESPROC)(GLfixed,GLfixed,GLfixed,GLfixed);
#endif
#if !defined(PFNGLRECTXVOESPROC)
typedef void(*PFNGLRECTXVOESPROC)(const GLfixed*,const GLfixed*);
#endif
#if !defined(PFNGLREFERENCEPLANESGIXPROC)
typedef void(*PFNGLREFERENCEPLANESGIXPROC)(const GLdouble*);
#endif
#if !defined(PFNGLRELEASESHADERCOMPILERPROC)
typedef void(*PFNGLRELEASESHADERCOMPILERPROC)();
#endif
#if !defined(PFNGLRENDERBUFFERSTORAGEEXTPROC)
typedef void(*PFNGLRENDERBUFFERSTORAGEEXTPROC)(GLenum,GLenum,GLsizei,GLsizei);
#endif
#if !defined(PFNGLRENDERBUFFERSTORAGEPROC)
typedef void(*PFNGLRENDERBUFFERSTORAGEPROC)(GLenum,GLenum,GLsizei,GLsizei);
#endif
#if !defined(PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC)
typedef void(*PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC)(GLenum,GLsizei,GLsizei,GLenum,GLsizei,GLsizei);
#endif
#if !defined(PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC)
typedef void(*PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC)(GLenum,GLsizei,GLenum,GLsizei,GLsizei);
#endif
#if !defined(PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)
typedef void(*PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)(GLenum,GLsizei,GLenum,GLsizei,GLsizei);
#endif
#if !defined(PFNGLREPLACEMENTCODEPOINTERSUNPROC)
typedef void(*PFNGLREPLACEMENTCODEPOINTERSUNPROC)(GLenum,GLsizei,const void**);
#endif
#if !defined(PFNGLREPLACEMENTCODEUBSUNPROC)
typedef void(*PFNGLREPLACEMENTCODEUBSUNPROC)(GLubyte);
#endif
#if !defined(PFNGLREPLACEMENTCODEUBVSUNPROC)
typedef void(*PFNGLREPLACEMENTCODEUBVSUNPROC)(const GLubyte*);
#endif
#if !defined(PFNGLREPLACEMENTCODEUICOLOR3FVERTEX3FSUNPROC)
typedef void(*PFNGLREPLACEMENTCODEUICOLOR3FVERTEX3FSUNPROC)(GLuint,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLREPLACEMENTCODEUICOLOR3FVERTEX3FVSUNPROC)
typedef void(*PFNGLREPLACEMENTCODEUICOLOR3FVERTEX3FVSUNPROC)(const GLuint*,const GLfloat*,const GLfloat*);
#endif
#if !defined(PFNGLREPLACEMENTCODEUICOLOR4FNORMAL3FVERTEX3FSUNPROC)
typedef void(*PFNGLREPLACEMENTCODEUICOLOR4FNORMAL3FVERTEX3FSUNPROC)(GLuint,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLREPLACEMENTCODEUICOLOR4FNORMAL3FVERTEX3FVSUNPROC)
typedef void(*PFNGLREPLACEMENTCODEUICOLOR4FNORMAL3FVERTEX3FVSUNPROC)(const GLuint*,const GLfloat*,const GLfloat*,const GLfloat*);
#endif
#if !defined(PFNGLREPLACEMENTCODEUICOLOR4UBVERTEX3FSUNPROC)
typedef void(*PFNGLREPLACEMENTCODEUICOLOR4UBVERTEX3FSUNPROC)(GLuint,GLubyte,GLubyte,GLubyte,GLubyte,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLREPLACEMENTCODEUICOLOR4UBVERTEX3FVSUNPROC)
typedef void(*PFNGLREPLACEMENTCODEUICOLOR4UBVERTEX3FVSUNPROC)(const GLuint*,const GLubyte*,const GLfloat*);
#endif
#if !defined(PFNGLREPLACEMENTCODEUINORMAL3FVERTEX3FSUNPROC)
typedef void(*PFNGLREPLACEMENTCODEUINORMAL3FVERTEX3FSUNPROC)(GLuint,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLREPLACEMENTCODEUINORMAL3FVERTEX3FVSUNPROC)
typedef void(*PFNGLREPLACEMENTCODEUINORMAL3FVERTEX3FVSUNPROC)(const GLuint*,const GLfloat*,const GLfloat*);
#endif
#if !defined(PFNGLREPLACEMENTCODEUISUNPROC)
typedef void(*PFNGLREPLACEMENTCODEUISUNPROC)(GLuint);
#endif
#if !defined(PFNGLREPLACEMENTCODEUITEXCOORD2FCOLOR4FNORMAL3FVERTEX3FSUNPROC)
typedef void(*PFNGLREPLACEMENTCODEUITEXCOORD2FCOLOR4FNORMAL3FVERTEX3FSUNPROC)(GLuint,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLREPLACEMENTCODEUITEXCOORD2FCOLOR4FNORMAL3FVERTEX3FVSUNPROC)
typedef void(*PFNGLREPLACEMENTCODEUITEXCOORD2FCOLOR4FNORMAL3FVERTEX3FVSUNPROC)(const GLuint*,const GLfloat*,const GLfloat*,const GLfloat*,const GLfloat*);
#endif
#if !defined(PFNGLREPLACEMENTCODEUITEXCOORD2FNORMAL3FVERTEX3FSUNPROC)
typedef void(*PFNGLREPLACEMENTCODEUITEXCOORD2FNORMAL3FVERTEX3FSUNPROC)(GLuint,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLREPLACEMENTCODEUITEXCOORD2FNORMAL3FVERTEX3FVSUNPROC)
typedef void(*PFNGLREPLACEMENTCODEUITEXCOORD2FNORMAL3FVERTEX3FVSUNPROC)(const GLuint*,const GLfloat*,const GLfloat*,const GLfloat*);
#endif
#if !defined(PFNGLREPLACEMENTCODEUITEXCOORD2FVERTEX3FSUNPROC)
typedef void(*PFNGLREPLACEMENTCODEUITEXCOORD2FVERTEX3FSUNPROC)(GLuint,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLREPLACEMENTCODEUITEXCOORD2FVERTEX3FVSUNPROC)
typedef void(*PFNGLREPLACEMENTCODEUITEXCOORD2FVERTEX3FVSUNPROC)(const GLuint*,const GLfloat*,const GLfloat*);
#endif
#if !defined(PFNGLREPLACEMENTCODEUIVERTEX3FSUNPROC)
typedef void(*PFNGLREPLACEMENTCODEUIVERTEX3FSUNPROC)(GLuint,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLREPLACEMENTCODEUIVERTEX3FVSUNPROC)
typedef void(*PFNGLREPLACEMENTCODEUIVERTEX3FVSUNPROC)(const GLuint*,const GLfloat*);
#endif
#if !defined(PFNGLREPLACEMENTCODEUIVSUNPROC)
typedef void(*PFNGLREPLACEMENTCODEUIVSUNPROC)(const GLuint*);
#endif
#if !defined(PFNGLREPLACEMENTCODEUSSUNPROC)
typedef void(*PFNGLREPLACEMENTCODEUSSUNPROC)(GLushort);
#endif
#if !defined(PFNGLREPLACEMENTCODEUSVSUNPROC)
typedef void(*PFNGLREPLACEMENTCODEUSVSUNPROC)(const GLushort*);
#endif
#if !defined(PFNGLREQUESTRESIDENTPROGRAMSNVPROC)
typedef void(*PFNGLREQUESTRESIDENTPROGRAMSNVPROC)(GLsizei,const GLuint*);
#endif
#if !defined(PFNGLRESETHISTOGRAMEXTPROC)
typedef void(*PFNGLRESETHISTOGRAMEXTPROC)(GLenum);
#endif
#if !defined(PFNGLRESETHISTOGRAMPROC)
typedef void(*PFNGLRESETHISTOGRAMPROC)(GLenum);
#endif
#if !defined(PFNGLRESETMINMAXEXTPROC)
typedef void(*PFNGLRESETMINMAXEXTPROC)(GLenum);
#endif
#if !defined(PFNGLRESETMINMAXPROC)
typedef void(*PFNGLRESETMINMAXPROC)(GLenum);
#endif
#if !defined(PFNGLRESIZEBUFFERSMESAPROC)
typedef void(*PFNGLRESIZEBUFFERSMESAPROC)();
#endif
#if !defined(PFNGLRESOLVEDEPTHVALUESNVPROC)
typedef void(*PFNGLRESOLVEDEPTHVALUESNVPROC)();
#endif
#if !defined(PFNGLRESUMETRANSFORMFEEDBACKPROC)
typedef void(*PFNGLRESUMETRANSFORMFEEDBACKPROC)();
#endif
#if !defined(PFNGLRESUMETRANSFORMFEEDBACKNVPROC)
typedef void(*PFNGLRESUMETRANSFORMFEEDBACKNVPROC)();
#endif
#if !defined(PFNGLROTATEDPROC)
typedef void(*PFNGLROTATEDPROC)(GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLROTATEFPROC)
typedef void(*PFNGLROTATEFPROC)(GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLROTATEXOESPROC)
typedef void(*PFNGLROTATEXOESPROC)(GLfixed,GLfixed,GLfixed,GLfixed);
#endif
#if !defined(PFNGLSAMPLECOVERAGEARBPROC)
typedef void(*PFNGLSAMPLECOVERAGEARBPROC)(GLfloat,GLboolean);
#endif
#if !defined(PFNGLSAMPLECOVERAGEPROC)
typedef void(*PFNGLSAMPLECOVERAGEPROC)(GLclampf,GLboolean);
#endif
#if !defined(PFNGLSAMPLEMAPATIPROC)
typedef void(*PFNGLSAMPLEMAPATIPROC)(GLuint,GLuint,GLenum);
#endif
#if !defined(PFNGLSAMPLEMASKEXTPROC)
typedef void(*PFNGLSAMPLEMASKEXTPROC)(GLclampf,GLboolean);
#endif
#if !defined(PFNGLSAMPLEMASKIPROC)
typedef void(*PFNGLSAMPLEMASKIPROC)(GLuint,GLbitfield);
#endif
#if !defined(PFNGLSAMPLEMASKINDEXEDNVPROC)
typedef void(*PFNGLSAMPLEMASKINDEXEDNVPROC)(GLuint,GLbitfield);
#endif
#if !defined(PFNGLSAMPLEMASKSGISPROC)
typedef void(*PFNGLSAMPLEMASKSGISPROC)(GLclampf,GLboolean);
#endif
#if !defined(PFNGLSAMPLEPATTERNEXTPROC)
typedef void(*PFNGLSAMPLEPATTERNEXTPROC)(GLenum);
#endif
#if !defined(PFNGLSAMPLEPATTERNSGISPROC)
typedef void(*PFNGLSAMPLEPATTERNSGISPROC)(GLenum);
#endif
#if !defined(PFNGLSAMPLERPARAMETERFPROC)
typedef void(*PFNGLSAMPLERPARAMETERFPROC)(GLuint,GLenum,GLfloat);
#endif
#if !defined(PFNGLSAMPLERPARAMETERFVPROC)
typedef void(*PFNGLSAMPLERPARAMETERFVPROC)(GLuint,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLSAMPLERPARAMETERIPROC)
typedef void(*PFNGLSAMPLERPARAMETERIPROC)(GLuint,GLenum,GLint);
#endif
#if !defined(PFNGLSAMPLERPARAMETERIIVPROC)
typedef void(*PFNGLSAMPLERPARAMETERIIVPROC)(GLuint,GLenum,const GLint*);
#endif
#if !defined(PFNGLSAMPLERPARAMETERIUIVPROC)
typedef void(*PFNGLSAMPLERPARAMETERIUIVPROC)(GLuint,GLenum,const GLuint*);
#endif
#if !defined(PFNGLSAMPLERPARAMETERIVPROC)
typedef void(*PFNGLSAMPLERPARAMETERIVPROC)(GLuint,GLenum,const GLint*);
#endif
#if !defined(PFNGLSCALEDPROC)
typedef void(*PFNGLSCALEDPROC)(GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLSCALEFPROC)
typedef void(*PFNGLSCALEFPROC)(GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLSCALEXOESPROC)
typedef void(*PFNGLSCALEXOESPROC)(GLfixed,GLfixed,GLfixed);
#endif
#if !defined(PFNGLSCISSORARRAYVPROC)
typedef void(*PFNGLSCISSORARRAYVPROC)(GLuint,GLsizei,const GLint*);
#endif
#if !defined(PFNGLSCISSORPROC)
typedef void(*PFNGLSCISSORPROC)(GLint,GLint,GLsizei,GLsizei);
#endif
#if !defined(PFNGLSCISSORINDEXEDPROC)
typedef void(*PFNGLSCISSORINDEXEDPROC)(GLuint,GLint,GLint,GLsizei,GLsizei);
#endif
#if !defined(PFNGLSCISSORINDEXEDVPROC)
typedef void(*PFNGLSCISSORINDEXEDVPROC)(GLuint,const GLint*);
#endif
#if !defined(PFNGLSECONDARYCOLOR3BEXTPROC)
typedef void(*PFNGLSECONDARYCOLOR3BEXTPROC)(GLbyte,GLbyte,GLbyte);
#endif
#if !defined(PFNGLSECONDARYCOLOR3BPROC)
typedef void(*PFNGLSECONDARYCOLOR3BPROC)(GLbyte,GLbyte,GLbyte);
#endif
#if !defined(PFNGLSECONDARYCOLOR3BVPROC)
typedef void(*PFNGLSECONDARYCOLOR3BVPROC)(const GLbyte*);
#endif
#if !defined(PFNGLSECONDARYCOLOR3BVEXTPROC)
typedef void(*PFNGLSECONDARYCOLOR3BVEXTPROC)(const GLbyte*);
#endif
#if !defined(PFNGLSECONDARYCOLOR3DEXTPROC)
typedef void(*PFNGLSECONDARYCOLOR3DEXTPROC)(GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLSECONDARYCOLOR3DPROC)
typedef void(*PFNGLSECONDARYCOLOR3DPROC)(GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLSECONDARYCOLOR3DVPROC)
typedef void(*PFNGLSECONDARYCOLOR3DVPROC)(const GLdouble*);
#endif
#if !defined(PFNGLSECONDARYCOLOR3DVEXTPROC)
typedef void(*PFNGLSECONDARYCOLOR3DVEXTPROC)(const GLdouble*);
#endif
#if !defined(PFNGLSECONDARYCOLOR3FEXTPROC)
typedef void(*PFNGLSECONDARYCOLOR3FEXTPROC)(GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLSECONDARYCOLOR3FPROC)
typedef void(*PFNGLSECONDARYCOLOR3FPROC)(GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLSECONDARYCOLOR3FVPROC)
typedef void(*PFNGLSECONDARYCOLOR3FVPROC)(const GLfloat*);
#endif
#if !defined(PFNGLSECONDARYCOLOR3FVEXTPROC)
typedef void(*PFNGLSECONDARYCOLOR3FVEXTPROC)(const GLfloat*);
#endif
#if !defined(PFNGLSECONDARYCOLOR3HNVPROC)
typedef void(*PFNGLSECONDARYCOLOR3HNVPROC)(GLhalfNV,GLhalfNV,GLhalfNV);
#endif
#if !defined(PFNGLSECONDARYCOLOR3HVNVPROC)
typedef void(*PFNGLSECONDARYCOLOR3HVNVPROC)(const GLhalfNV*);
#endif
#if !defined(PFNGLSECONDARYCOLOR3IEXTPROC)
typedef void(*PFNGLSECONDARYCOLOR3IEXTPROC)(GLint,GLint,GLint);
#endif
#if !defined(PFNGLSECONDARYCOLOR3IPROC)
typedef void(*PFNGLSECONDARYCOLOR3IPROC)(GLint,GLint,GLint);
#endif
#if !defined(PFNGLSECONDARYCOLOR3IVPROC)
typedef void(*PFNGLSECONDARYCOLOR3IVPROC)(const GLint*);
#endif
#if !defined(PFNGLSECONDARYCOLOR3IVEXTPROC)
typedef void(*PFNGLSECONDARYCOLOR3IVEXTPROC)(const GLint*);
#endif
#if !defined(PFNGLSECONDARYCOLOR3SEXTPROC)
typedef void(*PFNGLSECONDARYCOLOR3SEXTPROC)(GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLSECONDARYCOLOR3SPROC)
typedef void(*PFNGLSECONDARYCOLOR3SPROC)(GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLSECONDARYCOLOR3SVPROC)
typedef void(*PFNGLSECONDARYCOLOR3SVPROC)(const GLshort*);
#endif
#if !defined(PFNGLSECONDARYCOLOR3SVEXTPROC)
typedef void(*PFNGLSECONDARYCOLOR3SVEXTPROC)(const GLshort*);
#endif
#if !defined(PFNGLSECONDARYCOLOR3UBEXTPROC)
typedef void(*PFNGLSECONDARYCOLOR3UBEXTPROC)(GLubyte,GLubyte,GLubyte);
#endif
#if !defined(PFNGLSECONDARYCOLOR3UBPROC)
typedef void(*PFNGLSECONDARYCOLOR3UBPROC)(GLubyte,GLubyte,GLubyte);
#endif
#if !defined(PFNGLSECONDARYCOLOR3UBVPROC)
typedef void(*PFNGLSECONDARYCOLOR3UBVPROC)(const GLubyte*);
#endif
#if !defined(PFNGLSECONDARYCOLOR3UBVEXTPROC)
typedef void(*PFNGLSECONDARYCOLOR3UBVEXTPROC)(const GLubyte*);
#endif
#if !defined(PFNGLSECONDARYCOLOR3UIEXTPROC)
typedef void(*PFNGLSECONDARYCOLOR3UIEXTPROC)(GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLSECONDARYCOLOR3UIPROC)
typedef void(*PFNGLSECONDARYCOLOR3UIPROC)(GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLSECONDARYCOLOR3UIVPROC)
typedef void(*PFNGLSECONDARYCOLOR3UIVPROC)(const GLuint*);
#endif
#if !defined(PFNGLSECONDARYCOLOR3UIVEXTPROC)
typedef void(*PFNGLSECONDARYCOLOR3UIVEXTPROC)(const GLuint*);
#endif
#if !defined(PFNGLSECONDARYCOLOR3USEXTPROC)
typedef void(*PFNGLSECONDARYCOLOR3USEXTPROC)(GLushort,GLushort,GLushort);
#endif
#if !defined(PFNGLSECONDARYCOLOR3USPROC)
typedef void(*PFNGLSECONDARYCOLOR3USPROC)(GLushort,GLushort,GLushort);
#endif
#if !defined(PFNGLSECONDARYCOLOR3USVPROC)
typedef void(*PFNGLSECONDARYCOLOR3USVPROC)(const GLushort*);
#endif
#if !defined(PFNGLSECONDARYCOLOR3USVEXTPROC)
typedef void(*PFNGLSECONDARYCOLOR3USVEXTPROC)(const GLushort*);
#endif
#if !defined(PFNGLSECONDARYCOLORFORMATNVPROC)
typedef void(*PFNGLSECONDARYCOLORFORMATNVPROC)(GLint,GLenum,GLsizei);
#endif
#if !defined(PFNGLSECONDARYCOLORP3UIPROC)
typedef void(*PFNGLSECONDARYCOLORP3UIPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLSECONDARYCOLORP3UIVPROC)
typedef void(*PFNGLSECONDARYCOLORP3UIVPROC)(GLenum,const GLuint*);
#endif
#if !defined(PFNGLSECONDARYCOLORPOINTEREXTPROC)
typedef void(*PFNGLSECONDARYCOLORPOINTEREXTPROC)(GLint,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLSECONDARYCOLORPOINTERPROC)
typedef void(*PFNGLSECONDARYCOLORPOINTERPROC)(GLint,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLSECONDARYCOLORPOINTERLISTIBMPROC)
typedef void(*PFNGLSECONDARYCOLORPOINTERLISTIBMPROC)(GLint,GLenum,GLint,const void**,GLint);
#endif
#if !defined(PFNGLSELECTBUFFERPROC)
typedef void(*PFNGLSELECTBUFFERPROC)(GLsizei,GLuint*);
#endif
#if !defined(PFNGLSELECTPERFMONITORCOUNTERSAMDPROC)
typedef void(*PFNGLSELECTPERFMONITORCOUNTERSAMDPROC)(GLuint,GLboolean,GLuint,GLint,GLuint*);
#endif
#if !defined(PFNGLSEPARABLEFILTER2DEXTPROC)
typedef void(*PFNGLSEPARABLEFILTER2DEXTPROC)(GLenum,GLenum,GLsizei,GLsizei,GLenum,GLenum,const void*,const void*);
#endif
#if !defined(PFNGLSEPARABLEFILTER2DPROC)
typedef void(*PFNGLSEPARABLEFILTER2DPROC)(GLenum,GLenum,GLsizei,GLsizei,GLenum,GLenum,const GLvoid*,const GLvoid*);
#endif
#if !defined(PFNGLSETFENCEAPPLEPROC)
typedef void(*PFNGLSETFENCEAPPLEPROC)(GLuint);
#endif
#if !defined(PFNGLSETFENCENVPROC)
typedef void(*PFNGLSETFENCENVPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLSETFRAGMENTSHADERCONSTANTATIPROC)
typedef void(*PFNGLSETFRAGMENTSHADERCONSTANTATIPROC)(GLuint,const GLfloat*);
#endif
#if !defined(PFNGLSETINVARIANTEXTPROC)
typedef void(*PFNGLSETINVARIANTEXTPROC)(GLuint,GLenum,const void*);
#endif
#if !defined(PFNGLSETLOCALCONSTANTEXTPROC)
typedef void(*PFNGLSETLOCALCONSTANTEXTPROC)(GLuint,GLenum,const void*);
#endif
#if !defined(PFNGLSETMULTISAMPLEFVAMDPROC)
typedef void(*PFNGLSETMULTISAMPLEFVAMDPROC)(GLenum,GLuint,const GLfloat*);
#endif
#if !defined(PFNGLSHADEMODELPROC)
typedef void(*PFNGLSHADEMODELPROC)(GLenum);
#endif
#if !defined(PFNGLSHADERBINARYPROC)
typedef void(*PFNGLSHADERBINARYPROC)(GLsizei,const GLuint*,GLenum,const void*,GLsizei);
#endif
#if !defined(PFNGLSHADEROP1EXTPROC)
typedef void(*PFNGLSHADEROP1EXTPROC)(GLenum,GLuint,GLuint);
#endif
#if !defined(PFNGLSHADEROP2EXTPROC)
typedef void(*PFNGLSHADEROP2EXTPROC)(GLenum,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLSHADEROP3EXTPROC)
typedef void(*PFNGLSHADEROP3EXTPROC)(GLenum,GLuint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLSHADERSOURCEARBPROC)
typedef void(*PFNGLSHADERSOURCEARBPROC)(GLhandleARB,GLsizei,const GLcharARB**,const GLint*);
#endif
#if !defined(PFNGLSHADERSOURCEPROC)
typedef void(*PFNGLSHADERSOURCEPROC)(GLuint,GLsizei,const GLchar*const*,const GLint*);
#endif
#if !defined(PFNGLSHADERSTORAGEBLOCKBINDINGPROC)
typedef void(*PFNGLSHADERSTORAGEBLOCKBINDINGPROC)(GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLSHARPENTEXFUNCSGISPROC)
typedef void(*PFNGLSHARPENTEXFUNCSGISPROC)(GLenum,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLSPRITEPARAMETERFSGIXPROC)
typedef void(*PFNGLSPRITEPARAMETERFSGIXPROC)(GLenum,GLfloat);
#endif
#if !defined(PFNGLSPRITEPARAMETERFVSGIXPROC)
typedef void(*PFNGLSPRITEPARAMETERFVSGIXPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLSPRITEPARAMETERISGIXPROC)
typedef void(*PFNGLSPRITEPARAMETERISGIXPROC)(GLenum,GLint);
#endif
#if !defined(PFNGLSPRITEPARAMETERIVSGIXPROC)
typedef void(*PFNGLSPRITEPARAMETERIVSGIXPROC)(GLenum,const GLint*);
#endif
#if !defined(PFNGLSTARTINSTRUMENTSSGIXPROC)
typedef void(*PFNGLSTARTINSTRUMENTSSGIXPROC)();
#endif
#if !defined(PFNGLSTATECAPTURENVPROC)
typedef void(*PFNGLSTATECAPTURENVPROC)(GLuint,GLenum);
#endif
#if !defined(PFNGLSTENCILCLEARTAGEXTPROC)
typedef void(*PFNGLSTENCILCLEARTAGEXTPROC)(GLsizei,GLuint);
#endif
#if !defined(PFNGLSTENCILFILLPATHINSTANCEDNVPROC)
typedef void(*PFNGLSTENCILFILLPATHINSTANCEDNVPROC)(GLsizei,GLenum,const void*,GLuint,GLenum,GLuint,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLSTENCILFILLPATHNVPROC)
typedef void(*PFNGLSTENCILFILLPATHNVPROC)(GLuint,GLenum,GLuint);
#endif
#if !defined(PFNGLSTENCILFUNCPROC)
typedef void(*PFNGLSTENCILFUNCPROC)(GLenum,GLint,GLuint);
#endif
#if !defined(PFNGLSTENCILFUNCSEPARATEATIPROC)
typedef void(*PFNGLSTENCILFUNCSEPARATEATIPROC)(GLenum,GLenum,GLint,GLuint);
#endif
#if !defined(PFNGLSTENCILFUNCSEPARATEPROC)
typedef void(*PFNGLSTENCILFUNCSEPARATEPROC)(GLenum,GLenum,GLint,GLuint);
#endif
#if !defined(PFNGLSTENCILMASKPROC)
typedef void(*PFNGLSTENCILMASKPROC)(GLuint);
#endif
#if !defined(PFNGLSTENCILMASKSEPARATEPROC)
typedef void(*PFNGLSTENCILMASKSEPARATEPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLSTENCILOPPROC)
typedef void(*PFNGLSTENCILOPPROC)(GLenum,GLenum,GLenum);
#endif
#if !defined(PFNGLSTENCILOPSEPARATEATIPROC)
typedef void(*PFNGLSTENCILOPSEPARATEATIPROC)(GLenum,GLenum,GLenum,GLenum);
#endif
#if !defined(PFNGLSTENCILOPSEPARATEPROC)
typedef void(*PFNGLSTENCILOPSEPARATEPROC)(GLenum,GLenum,GLenum,GLenum);
#endif
#if !defined(PFNGLSTENCILOPVALUEAMDPROC)
typedef void(*PFNGLSTENCILOPVALUEAMDPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC)
typedef void(*PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC)(GLsizei,GLenum,const void*,GLuint,GLint,GLuint,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLSTENCILSTROKEPATHNVPROC)
typedef void(*PFNGLSTENCILSTROKEPATHNVPROC)(GLuint,GLint,GLuint);
#endif
#if !defined(PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC)
typedef void(*PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC)(GLsizei,GLenum,const void*,GLuint,GLenum,GLuint,GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLSTENCILTHENCOVERFILLPATHNVPROC)
typedef void(*PFNGLSTENCILTHENCOVERFILLPATHNVPROC)(GLuint,GLenum,GLuint,GLenum);
#endif
#if !defined(PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC)
typedef void(*PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC)(GLsizei,GLenum,const void*,GLuint,GLint,GLuint,GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC)
typedef void(*PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC)(GLuint,GLint,GLuint,GLenum);
#endif
#if !defined(PFNGLSTOPINSTRUMENTSSGIXPROC)
typedef void(*PFNGLSTOPINSTRUMENTSSGIXPROC)(GLint);
#endif
#if !defined(PFNGLSTRINGMARKERGREMEDYPROC)
typedef void(*PFNGLSTRINGMARKERGREMEDYPROC)(GLsizei,const void*);
#endif
#if !defined(PFNGLSUBPIXELPRECISIONBIASNVPROC)
typedef void(*PFNGLSUBPIXELPRECISIONBIASNVPROC)(GLuint,GLuint);
#endif
#if !defined(PFNGLSWIZZLEEXTPROC)
typedef void(*PFNGLSWIZZLEEXTPROC)(GLuint,GLuint,GLenum,GLenum,GLenum,GLenum);
#endif
#if !defined(PFNGLSYNCTEXTUREINTELPROC)
typedef void(*PFNGLSYNCTEXTUREINTELPROC)(GLuint);
#endif
#if !defined(PFNGLTAGSAMPLEBUFFERSGIXPROC)
typedef void(*PFNGLTAGSAMPLEBUFFERSGIXPROC)();
#endif
#if !defined(PFNGLTANGENT3BEXTPROC)
typedef void(*PFNGLTANGENT3BEXTPROC)(GLbyte,GLbyte,GLbyte);
#endif
#if !defined(PFNGLTANGENT3BVEXTPROC)
typedef void(*PFNGLTANGENT3BVEXTPROC)(const GLbyte*);
#endif
#if !defined(PFNGLTANGENT3DEXTPROC)
typedef void(*PFNGLTANGENT3DEXTPROC)(GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLTANGENT3DVEXTPROC)
typedef void(*PFNGLTANGENT3DVEXTPROC)(const GLdouble*);
#endif
#if !defined(PFNGLTANGENT3FEXTPROC)
typedef void(*PFNGLTANGENT3FEXTPROC)(GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLTANGENT3FVEXTPROC)
typedef void(*PFNGLTANGENT3FVEXTPROC)(const GLfloat*);
#endif
#if !defined(PFNGLTANGENT3IEXTPROC)
typedef void(*PFNGLTANGENT3IEXTPROC)(GLint,GLint,GLint);
#endif
#if !defined(PFNGLTANGENT3IVEXTPROC)
typedef void(*PFNGLTANGENT3IVEXTPROC)(const GLint*);
#endif
#if !defined(PFNGLTANGENT3SEXTPROC)
typedef void(*PFNGLTANGENT3SEXTPROC)(GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLTANGENT3SVEXTPROC)
typedef void(*PFNGLTANGENT3SVEXTPROC)(const GLshort*);
#endif
#if !defined(PFNGLTANGENTPOINTEREXTPROC)
typedef void(*PFNGLTANGENTPOINTEREXTPROC)(GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLTBUFFERMASK3DFXPROC)
typedef void(*PFNGLTBUFFERMASK3DFXPROC)(GLuint);
#endif
#if !defined(PFNGLTESSELLATIONFACTORAMDPROC)
typedef void(*PFNGLTESSELLATIONFACTORAMDPROC)(GLfloat);
#endif
#if !defined(PFNGLTESSELLATIONMODEAMDPROC)
typedef void(*PFNGLTESSELLATIONMODEAMDPROC)(GLenum);
#endif
#if !defined(PFNGLTEXBUFFERARBPROC)
typedef void(*PFNGLTEXBUFFERARBPROC)(GLenum,GLenum,GLuint);
#endif
#if !defined(PFNGLTEXBUFFEREXTPROC)
typedef void(*PFNGLTEXBUFFEREXTPROC)(GLenum,GLenum,GLuint);
#endif
#if !defined(PFNGLTEXBUFFERPROC)
typedef void(*PFNGLTEXBUFFERPROC)(GLenum,GLenum,GLuint);
#endif
#if !defined(PFNGLTEXBUFFERRANGEPROC)
typedef void(*PFNGLTEXBUFFERRANGEPROC)(GLenum,GLenum,GLuint,GLintptr,GLsizeiptr);
#endif
#if !defined(PFNGLTEXBUMPPARAMETERFVATIPROC)
typedef void(*PFNGLTEXBUMPPARAMETERFVATIPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLTEXBUMPPARAMETERIVATIPROC)
typedef void(*PFNGLTEXBUMPPARAMETERIVATIPROC)(GLenum,const GLint*);
#endif
#if !defined(PFNGLTEXCOORD1BOESPROC)
typedef void(*PFNGLTEXCOORD1BOESPROC)(GLbyte);
#endif
#if !defined(PFNGLTEXCOORD1BVOESPROC)
typedef void(*PFNGLTEXCOORD1BVOESPROC)(const GLbyte*);
#endif
#if !defined(PFNGLTEXCOORD1DPROC)
typedef void(*PFNGLTEXCOORD1DPROC)(GLdouble);
#endif
#if !defined(PFNGLTEXCOORD1DVPROC)
typedef void(*PFNGLTEXCOORD1DVPROC)(const GLdouble*);
#endif
#if !defined(PFNGLTEXCOORD1FPROC)
typedef void(*PFNGLTEXCOORD1FPROC)(GLfloat);
#endif
#if !defined(PFNGLTEXCOORD1FVPROC)
typedef void(*PFNGLTEXCOORD1FVPROC)(const GLfloat*);
#endif
#if !defined(PFNGLTEXCOORD1HNVPROC)
typedef void(*PFNGLTEXCOORD1HNVPROC)(GLhalfNV);
#endif
#if !defined(PFNGLTEXCOORD1HVNVPROC)
typedef void(*PFNGLTEXCOORD1HVNVPROC)(const GLhalfNV*);
#endif
#if !defined(PFNGLTEXCOORD1IPROC)
typedef void(*PFNGLTEXCOORD1IPROC)(GLint);
#endif
#if !defined(PFNGLTEXCOORD1IVPROC)
typedef void(*PFNGLTEXCOORD1IVPROC)(const GLint*);
#endif
#if !defined(PFNGLTEXCOORD1SPROC)
typedef void(*PFNGLTEXCOORD1SPROC)(GLshort);
#endif
#if !defined(PFNGLTEXCOORD1SVPROC)
typedef void(*PFNGLTEXCOORD1SVPROC)(const GLshort*);
#endif
#if !defined(PFNGLTEXCOORD1XOESPROC)
typedef void(*PFNGLTEXCOORD1XOESPROC)(GLfixed);
#endif
#if !defined(PFNGLTEXCOORD1XVOESPROC)
typedef void(*PFNGLTEXCOORD1XVOESPROC)(const GLfixed*);
#endif
#if !defined(PFNGLTEXCOORD2BOESPROC)
typedef void(*PFNGLTEXCOORD2BOESPROC)(GLbyte,GLbyte);
#endif
#if !defined(PFNGLTEXCOORD2BVOESPROC)
typedef void(*PFNGLTEXCOORD2BVOESPROC)(const GLbyte*);
#endif
#if !defined(PFNGLTEXCOORD2DPROC)
typedef void(*PFNGLTEXCOORD2DPROC)(GLdouble,GLdouble);
#endif
#if !defined(PFNGLTEXCOORD2DVPROC)
typedef void(*PFNGLTEXCOORD2DVPROC)(const GLdouble*);
#endif
#if !defined(PFNGLTEXCOORD2FCOLOR3FVERTEX3FSUNPROC)
typedef void(*PFNGLTEXCOORD2FCOLOR3FVERTEX3FSUNPROC)(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLTEXCOORD2FCOLOR3FVERTEX3FVSUNPROC)
typedef void(*PFNGLTEXCOORD2FCOLOR3FVERTEX3FVSUNPROC)(const GLfloat*,const GLfloat*,const GLfloat*);
#endif
#if !defined(PFNGLTEXCOORD2FCOLOR4FNORMAL3FVERTEX3FSUNPROC)
typedef void(*PFNGLTEXCOORD2FCOLOR4FNORMAL3FVERTEX3FSUNPROC)(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLTEXCOORD2FCOLOR4FNORMAL3FVERTEX3FVSUNPROC)
typedef void(*PFNGLTEXCOORD2FCOLOR4FNORMAL3FVERTEX3FVSUNPROC)(const GLfloat*,const GLfloat*,const GLfloat*,const GLfloat*);
#endif
#if !defined(PFNGLTEXCOORD2FCOLOR4UBVERTEX3FSUNPROC)
typedef void(*PFNGLTEXCOORD2FCOLOR4UBVERTEX3FSUNPROC)(GLfloat,GLfloat,GLubyte,GLubyte,GLubyte,GLubyte,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLTEXCOORD2FCOLOR4UBVERTEX3FVSUNPROC)
typedef void(*PFNGLTEXCOORD2FCOLOR4UBVERTEX3FVSUNPROC)(const GLfloat*,const GLubyte*,const GLfloat*);
#endif
#if !defined(PFNGLTEXCOORD2FPROC)
typedef void(*PFNGLTEXCOORD2FPROC)(GLfloat,GLfloat);
#endif
#if !defined(PFNGLTEXCOORD2FNORMAL3FVERTEX3FSUNPROC)
typedef void(*PFNGLTEXCOORD2FNORMAL3FVERTEX3FSUNPROC)(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLTEXCOORD2FNORMAL3FVERTEX3FVSUNPROC)
typedef void(*PFNGLTEXCOORD2FNORMAL3FVERTEX3FVSUNPROC)(const GLfloat*,const GLfloat*,const GLfloat*);
#endif
#if !defined(PFNGLTEXCOORD2FVPROC)
typedef void(*PFNGLTEXCOORD2FVPROC)(const GLfloat*);
#endif
#if !defined(PFNGLTEXCOORD2FVERTEX3FSUNPROC)
typedef void(*PFNGLTEXCOORD2FVERTEX3FSUNPROC)(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLTEXCOORD2FVERTEX3FVSUNPROC)
typedef void(*PFNGLTEXCOORD2FVERTEX3FVSUNPROC)(const GLfloat*,const GLfloat*);
#endif
#if !defined(PFNGLTEXCOORD2HNVPROC)
typedef void(*PFNGLTEXCOORD2HNVPROC)(GLhalfNV,GLhalfNV);
#endif
#if !defined(PFNGLTEXCOORD2HVNVPROC)
typedef void(*PFNGLTEXCOORD2HVNVPROC)(const GLhalfNV*);
#endif
#if !defined(PFNGLTEXCOORD2IPROC)
typedef void(*PFNGLTEXCOORD2IPROC)(GLint,GLint);
#endif
#if !defined(PFNGLTEXCOORD2IVPROC)
typedef void(*PFNGLTEXCOORD2IVPROC)(const GLint*);
#endif
#if !defined(PFNGLTEXCOORD2SPROC)
typedef void(*PFNGLTEXCOORD2SPROC)(GLshort,GLshort);
#endif
#if !defined(PFNGLTEXCOORD2SVPROC)
typedef void(*PFNGLTEXCOORD2SVPROC)(const GLshort*);
#endif
#if !defined(PFNGLTEXCOORD2XOESPROC)
typedef void(*PFNGLTEXCOORD2XOESPROC)(GLfixed,GLfixed);
#endif
#if !defined(PFNGLTEXCOORD2XVOESPROC)
typedef void(*PFNGLTEXCOORD2XVOESPROC)(const GLfixed*);
#endif
#if !defined(PFNGLTEXCOORD3BOESPROC)
typedef void(*PFNGLTEXCOORD3BOESPROC)(GLbyte,GLbyte,GLbyte);
#endif
#if !defined(PFNGLTEXCOORD3BVOESPROC)
typedef void(*PFNGLTEXCOORD3BVOESPROC)(const GLbyte*);
#endif
#if !defined(PFNGLTEXCOORD3DPROC)
typedef void(*PFNGLTEXCOORD3DPROC)(GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLTEXCOORD3DVPROC)
typedef void(*PFNGLTEXCOORD3DVPROC)(const GLdouble*);
#endif
#if !defined(PFNGLTEXCOORD3FPROC)
typedef void(*PFNGLTEXCOORD3FPROC)(GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLTEXCOORD3FVPROC)
typedef void(*PFNGLTEXCOORD3FVPROC)(const GLfloat*);
#endif
#if !defined(PFNGLTEXCOORD3HNVPROC)
typedef void(*PFNGLTEXCOORD3HNVPROC)(GLhalfNV,GLhalfNV,GLhalfNV);
#endif
#if !defined(PFNGLTEXCOORD3HVNVPROC)
typedef void(*PFNGLTEXCOORD3HVNVPROC)(const GLhalfNV*);
#endif
#if !defined(PFNGLTEXCOORD3IPROC)
typedef void(*PFNGLTEXCOORD3IPROC)(GLint,GLint,GLint);
#endif
#if !defined(PFNGLTEXCOORD3IVPROC)
typedef void(*PFNGLTEXCOORD3IVPROC)(const GLint*);
#endif
#if !defined(PFNGLTEXCOORD3SPROC)
typedef void(*PFNGLTEXCOORD3SPROC)(GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLTEXCOORD3SVPROC)
typedef void(*PFNGLTEXCOORD3SVPROC)(const GLshort*);
#endif
#if !defined(PFNGLTEXCOORD3XOESPROC)
typedef void(*PFNGLTEXCOORD3XOESPROC)(GLfixed,GLfixed,GLfixed);
#endif
#if !defined(PFNGLTEXCOORD3XVOESPROC)
typedef void(*PFNGLTEXCOORD3XVOESPROC)(const GLfixed*);
#endif
#if !defined(PFNGLTEXCOORD4BOESPROC)
typedef void(*PFNGLTEXCOORD4BOESPROC)(GLbyte,GLbyte,GLbyte,GLbyte);
#endif
#if !defined(PFNGLTEXCOORD4BVOESPROC)
typedef void(*PFNGLTEXCOORD4BVOESPROC)(const GLbyte*);
#endif
#if !defined(PFNGLTEXCOORD4DPROC)
typedef void(*PFNGLTEXCOORD4DPROC)(GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLTEXCOORD4DVPROC)
typedef void(*PFNGLTEXCOORD4DVPROC)(const GLdouble*);
#endif
#if !defined(PFNGLTEXCOORD4FCOLOR4FNORMAL3FVERTEX4FSUNPROC)
typedef void(*PFNGLTEXCOORD4FCOLOR4FNORMAL3FVERTEX4FSUNPROC)(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLTEXCOORD4FCOLOR4FNORMAL3FVERTEX4FVSUNPROC)
typedef void(*PFNGLTEXCOORD4FCOLOR4FNORMAL3FVERTEX4FVSUNPROC)(const GLfloat*,const GLfloat*,const GLfloat*,const GLfloat*);
#endif
#if !defined(PFNGLTEXCOORD4FPROC)
typedef void(*PFNGLTEXCOORD4FPROC)(GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLTEXCOORD4FVPROC)
typedef void(*PFNGLTEXCOORD4FVPROC)(const GLfloat*);
#endif
#if !defined(PFNGLTEXCOORD4FVERTEX4FSUNPROC)
typedef void(*PFNGLTEXCOORD4FVERTEX4FSUNPROC)(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLTEXCOORD4FVERTEX4FVSUNPROC)
typedef void(*PFNGLTEXCOORD4FVERTEX4FVSUNPROC)(const GLfloat*,const GLfloat*);
#endif
#if !defined(PFNGLTEXCOORD4HNVPROC)
typedef void(*PFNGLTEXCOORD4HNVPROC)(GLhalfNV,GLhalfNV,GLhalfNV,GLhalfNV);
#endif
#if !defined(PFNGLTEXCOORD4HVNVPROC)
typedef void(*PFNGLTEXCOORD4HVNVPROC)(const GLhalfNV*);
#endif
#if !defined(PFNGLTEXCOORD4IPROC)
typedef void(*PFNGLTEXCOORD4IPROC)(GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLTEXCOORD4IVPROC)
typedef void(*PFNGLTEXCOORD4IVPROC)(const GLint*);
#endif
#if !defined(PFNGLTEXCOORD4SPROC)
typedef void(*PFNGLTEXCOORD4SPROC)(GLshort,GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLTEXCOORD4SVPROC)
typedef void(*PFNGLTEXCOORD4SVPROC)(const GLshort*);
#endif
#if !defined(PFNGLTEXCOORD4XOESPROC)
typedef void(*PFNGLTEXCOORD4XOESPROC)(GLfixed,GLfixed,GLfixed,GLfixed);
#endif
#if !defined(PFNGLTEXCOORD4XVOESPROC)
typedef void(*PFNGLTEXCOORD4XVOESPROC)(const GLfixed*);
#endif
#if !defined(PFNGLTEXCOORDFORMATNVPROC)
typedef void(*PFNGLTEXCOORDFORMATNVPROC)(GLint,GLenum,GLsizei);
#endif
#if !defined(PFNGLTEXCOORDP1UIPROC)
typedef void(*PFNGLTEXCOORDP1UIPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLTEXCOORDP1UIVPROC)
typedef void(*PFNGLTEXCOORDP1UIVPROC)(GLenum,const GLuint*);
#endif
#if !defined(PFNGLTEXCOORDP2UIPROC)
typedef void(*PFNGLTEXCOORDP2UIPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLTEXCOORDP2UIVPROC)
typedef void(*PFNGLTEXCOORDP2UIVPROC)(GLenum,const GLuint*);
#endif
#if !defined(PFNGLTEXCOORDP3UIPROC)
typedef void(*PFNGLTEXCOORDP3UIPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLTEXCOORDP3UIVPROC)
typedef void(*PFNGLTEXCOORDP3UIVPROC)(GLenum,const GLuint*);
#endif
#if !defined(PFNGLTEXCOORDP4UIPROC)
typedef void(*PFNGLTEXCOORDP4UIPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLTEXCOORDP4UIVPROC)
typedef void(*PFNGLTEXCOORDP4UIVPROC)(GLenum,const GLuint*);
#endif
#if !defined(PFNGLTEXCOORDPOINTEREXTPROC)
typedef void(*PFNGLTEXCOORDPOINTEREXTPROC)(GLint,GLenum,GLsizei,GLsizei,const void*);
#endif
#if !defined(PFNGLTEXCOORDPOINTERPROC)
typedef void(*PFNGLTEXCOORDPOINTERPROC)(GLint,GLenum,GLsizei,const GLvoid*);
#endif
#if !defined(PFNGLTEXCOORDPOINTERLISTIBMPROC)
typedef void(*PFNGLTEXCOORDPOINTERLISTIBMPROC)(GLint,GLenum,GLint,const void**,GLint);
#endif
#if !defined(PFNGLTEXCOORDPOINTERVINTELPROC)
typedef void(*PFNGLTEXCOORDPOINTERVINTELPROC)(GLint,GLenum,const void**);
#endif
#if !defined(PFNGLTEXENVFPROC)
typedef void(*PFNGLTEXENVFPROC)(GLenum,GLenum,GLfloat);
#endif
#if !defined(PFNGLTEXENVFVPROC)
typedef void(*PFNGLTEXENVFVPROC)(GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLTEXENVIPROC)
typedef void(*PFNGLTEXENVIPROC)(GLenum,GLenum,GLint);
#endif
#if !defined(PFNGLTEXENVIVPROC)
typedef void(*PFNGLTEXENVIVPROC)(GLenum,GLenum,const GLint*);
#endif
#if !defined(PFNGLTEXENVXOESPROC)
typedef void(*PFNGLTEXENVXOESPROC)(GLenum,GLenum,GLfixed);
#endif
#if !defined(PFNGLTEXENVXVOESPROC)
typedef void(*PFNGLTEXENVXVOESPROC)(GLenum,GLenum,const GLfixed*);
#endif
#if !defined(PFNGLTEXFILTERFUNCSGISPROC)
typedef void(*PFNGLTEXFILTERFUNCSGISPROC)(GLenum,GLenum,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLTEXGENDPROC)
typedef void(*PFNGLTEXGENDPROC)(GLenum,GLenum,GLdouble);
#endif
#if !defined(PFNGLTEXGENDVPROC)
typedef void(*PFNGLTEXGENDVPROC)(GLenum,GLenum,const GLdouble*);
#endif
#if !defined(PFNGLTEXGENFPROC)
typedef void(*PFNGLTEXGENFPROC)(GLenum,GLenum,GLfloat);
#endif
#if !defined(PFNGLTEXGENFVPROC)
typedef void(*PFNGLTEXGENFVPROC)(GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLTEXGENIPROC)
typedef void(*PFNGLTEXGENIPROC)(GLenum,GLenum,GLint);
#endif
#if !defined(PFNGLTEXGENIVPROC)
typedef void(*PFNGLTEXGENIVPROC)(GLenum,GLenum,const GLint*);
#endif
#if !defined(PFNGLTEXGENXOESPROC)
typedef void(*PFNGLTEXGENXOESPROC)(GLenum,GLenum,GLfixed);
#endif
#if !defined(PFNGLTEXGENXVOESPROC)
typedef void(*PFNGLTEXGENXVOESPROC)(GLenum,GLenum,const GLfixed*);
#endif
#if !defined(PFNGLTEXIMAGE1DPROC)
typedef void(*PFNGLTEXIMAGE1DPROC)(GLenum,GLint,GLint,GLsizei,GLint,GLenum,GLenum,const GLvoid*);
#endif
#if !defined(PFNGLTEXIMAGE2DPROC)
typedef void(*PFNGLTEXIMAGE2DPROC)(GLenum,GLint,GLint,GLsizei,GLsizei,GLint,GLenum,GLenum,const GLvoid*);
#endif
#if !defined(PFNGLTEXIMAGE2DMULTISAMPLECOVERAGENVPROC)
typedef void(*PFNGLTEXIMAGE2DMULTISAMPLECOVERAGENVPROC)(GLenum,GLsizei,GLsizei,GLint,GLsizei,GLsizei,GLboolean);
#endif
#if !defined(PFNGLTEXIMAGE2DMULTISAMPLEPROC)
typedef void(*PFNGLTEXIMAGE2DMULTISAMPLEPROC)(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLboolean);
#endif
#if !defined(PFNGLTEXIMAGE3DEXTPROC)
typedef void(*PFNGLTEXIMAGE3DEXTPROC)(GLenum,GLint,GLenum,GLsizei,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLTEXIMAGE3DPROC)
typedef void(*PFNGLTEXIMAGE3DPROC)(GLenum,GLint,GLint,GLsizei,GLsizei,GLsizei,GLint,GLenum,GLenum,const GLvoid*);
#endif
#if !defined(PFNGLTEXIMAGE3DMULTISAMPLECOVERAGENVPROC)
typedef void(*PFNGLTEXIMAGE3DMULTISAMPLECOVERAGENVPROC)(GLenum,GLsizei,GLsizei,GLint,GLsizei,GLsizei,GLsizei,GLboolean);
#endif
#if !defined(PFNGLTEXIMAGE3DMULTISAMPLEPROC)
typedef void(*PFNGLTEXIMAGE3DMULTISAMPLEPROC)(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei,GLboolean);
#endif
#if !defined(PFNGLTEXIMAGE4DSGISPROC)
typedef void(*PFNGLTEXIMAGE4DSGISPROC)(GLenum,GLint,GLenum,GLsizei,GLsizei,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLTEXPAGECOMMITMENTARBPROC)
typedef void(*PFNGLTEXPAGECOMMITMENTARBPROC)(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLboolean);
#endif
#if !defined(PFNGLTEXPARAMETERFPROC)
typedef void(*PFNGLTEXPARAMETERFPROC)(GLenum,GLenum,GLfloat);
#endif
#if !defined(PFNGLTEXPARAMETERFVPROC)
typedef void(*PFNGLTEXPARAMETERFVPROC)(GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLTEXPARAMETERIPROC)
typedef void(*PFNGLTEXPARAMETERIPROC)(GLenum,GLenum,GLint);
#endif
#if !defined(PFNGLTEXPARAMETERIIVEXTPROC)
typedef void(*PFNGLTEXPARAMETERIIVEXTPROC)(GLenum,GLenum,const GLint*);
#endif
#if !defined(PFNGLTEXPARAMETERIIVPROC)
typedef void(*PFNGLTEXPARAMETERIIVPROC)(GLenum,GLenum,const GLint*);
#endif
#if !defined(PFNGLTEXPARAMETERIUIVEXTPROC)
typedef void(*PFNGLTEXPARAMETERIUIVEXTPROC)(GLenum,GLenum,const GLuint*);
#endif
#if !defined(PFNGLTEXPARAMETERIUIVPROC)
typedef void(*PFNGLTEXPARAMETERIUIVPROC)(GLenum,GLenum,const GLuint*);
#endif
#if !defined(PFNGLTEXPARAMETERIVPROC)
typedef void(*PFNGLTEXPARAMETERIVPROC)(GLenum,GLenum,const GLint*);
#endif
#if !defined(PFNGLTEXPARAMETERXOESPROC)
typedef void(*PFNGLTEXPARAMETERXOESPROC)(GLenum,GLenum,GLfixed);
#endif
#if !defined(PFNGLTEXPARAMETERXVOESPROC)
typedef void(*PFNGLTEXPARAMETERXVOESPROC)(GLenum,GLenum,const GLfixed*);
#endif
#if !defined(PFNGLTEXRENDERBUFFERNVPROC)
typedef void(*PFNGLTEXRENDERBUFFERNVPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLTEXSTORAGE1DPROC)
typedef void(*PFNGLTEXSTORAGE1DPROC)(GLenum,GLsizei,GLenum,GLsizei);
#endif
#if !defined(PFNGLTEXSTORAGE2DPROC)
typedef void(*PFNGLTEXSTORAGE2DPROC)(GLenum,GLsizei,GLenum,GLsizei,GLsizei);
#endif
#if !defined(PFNGLTEXSTORAGE2DMULTISAMPLEPROC)
typedef void(*PFNGLTEXSTORAGE2DMULTISAMPLEPROC)(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLboolean);
#endif
#if !defined(PFNGLTEXSTORAGE3DPROC)
typedef void(*PFNGLTEXSTORAGE3DPROC)(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei);
#endif
#if !defined(PFNGLTEXSTORAGE3DMULTISAMPLEPROC)
typedef void(*PFNGLTEXSTORAGE3DMULTISAMPLEPROC)(GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei,GLboolean);
#endif
#if !defined(PFNGLTEXSTORAGESPARSEAMDPROC)
typedef void(*PFNGLTEXSTORAGESPARSEAMDPROC)(GLenum,GLenum,GLsizei,GLsizei,GLsizei,GLsizei,GLbitfield);
#endif
#if !defined(PFNGLTEXSUBIMAGE1DEXTPROC)
typedef void(*PFNGLTEXSUBIMAGE1DEXTPROC)(GLenum,GLint,GLint,GLsizei,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLTEXSUBIMAGE1DPROC)
typedef void(*PFNGLTEXSUBIMAGE1DPROC)(GLenum,GLint,GLint,GLsizei,GLenum,GLenum,const GLvoid*);
#endif
#if !defined(PFNGLTEXSUBIMAGE2DEXTPROC)
typedef void(*PFNGLTEXSUBIMAGE2DEXTPROC)(GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLTEXSUBIMAGE2DPROC)
typedef void(*PFNGLTEXSUBIMAGE2DPROC)(GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,const GLvoid*);
#endif
#if !defined(PFNGLTEXSUBIMAGE3DEXTPROC)
typedef void(*PFNGLTEXSUBIMAGE3DEXTPROC)(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLTEXSUBIMAGE3DPROC)
typedef void(*PFNGLTEXSUBIMAGE3DPROC)(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const GLvoid*);
#endif
#if !defined(PFNGLTEXSUBIMAGE4DSGISPROC)
typedef void(*PFNGLTEXSUBIMAGE4DSGISPROC)(GLenum,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLTEXTUREBARRIERPROC)
typedef void(*PFNGLTEXTUREBARRIERPROC)();
#endif
#if !defined(PFNGLTEXTUREBARRIERNVPROC)
typedef void(*PFNGLTEXTUREBARRIERNVPROC)();
#endif
#if !defined(PFNGLTEXTUREBUFFEREXTPROC)
typedef void(*PFNGLTEXTUREBUFFEREXTPROC)(GLuint,GLenum,GLenum,GLuint);
#endif
#if !defined(PFNGLTEXTUREBUFFERPROC)
typedef void(*PFNGLTEXTUREBUFFERPROC)(GLuint,GLenum,GLuint);
#endif
#if !defined(PFNGLTEXTUREBUFFERRANGEEXTPROC)
typedef void(*PFNGLTEXTUREBUFFERRANGEEXTPROC)(GLuint,GLenum,GLenum,GLuint,GLintptr,GLsizeiptr);
#endif
#if !defined(PFNGLTEXTUREBUFFERRANGEPROC)
typedef void(*PFNGLTEXTUREBUFFERRANGEPROC)(GLuint,GLenum,GLuint,GLintptr,GLsizeiptr);
#endif
#if !defined(PFNGLTEXTURECOLORMASKSGISPROC)
typedef void(*PFNGLTEXTURECOLORMASKSGISPROC)(GLboolean,GLboolean,GLboolean,GLboolean);
#endif
#if !defined(PFNGLTEXTUREIMAGE1DEXTPROC)
typedef void(*PFNGLTEXTUREIMAGE1DEXTPROC)(GLuint,GLenum,GLint,GLint,GLsizei,GLint,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLTEXTUREIMAGE2DEXTPROC)
typedef void(*PFNGLTEXTUREIMAGE2DEXTPROC)(GLuint,GLenum,GLint,GLint,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLTEXTUREIMAGE2DMULTISAMPLECOVERAGENVPROC)
typedef void(*PFNGLTEXTUREIMAGE2DMULTISAMPLECOVERAGENVPROC)(GLuint,GLenum,GLsizei,GLsizei,GLint,GLsizei,GLsizei,GLboolean);
#endif
#if !defined(PFNGLTEXTUREIMAGE2DMULTISAMPLENVPROC)
typedef void(*PFNGLTEXTUREIMAGE2DMULTISAMPLENVPROC)(GLuint,GLenum,GLsizei,GLint,GLsizei,GLsizei,GLboolean);
#endif
#if !defined(PFNGLTEXTUREIMAGE3DEXTPROC)
typedef void(*PFNGLTEXTUREIMAGE3DEXTPROC)(GLuint,GLenum,GLint,GLint,GLsizei,GLsizei,GLsizei,GLint,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLTEXTUREIMAGE3DMULTISAMPLECOVERAGENVPROC)
typedef void(*PFNGLTEXTUREIMAGE3DMULTISAMPLECOVERAGENVPROC)(GLuint,GLenum,GLsizei,GLsizei,GLint,GLsizei,GLsizei,GLsizei,GLboolean);
#endif
#if !defined(PFNGLTEXTUREIMAGE3DMULTISAMPLENVPROC)
typedef void(*PFNGLTEXTUREIMAGE3DMULTISAMPLENVPROC)(GLuint,GLenum,GLsizei,GLint,GLsizei,GLsizei,GLsizei,GLboolean);
#endif
#if !defined(PFNGLTEXTURELIGHTEXTPROC)
typedef void(*PFNGLTEXTURELIGHTEXTPROC)(GLenum);
#endif
#if !defined(PFNGLTEXTUREMATERIALEXTPROC)
typedef void(*PFNGLTEXTUREMATERIALEXTPROC)(GLenum,GLenum);
#endif
#if !defined(PFNGLTEXTURENORMALEXTPROC)
typedef void(*PFNGLTEXTURENORMALEXTPROC)(GLenum);
#endif
#if !defined(PFNGLTEXTUREPAGECOMMITMENTEXTPROC)
typedef void(*PFNGLTEXTUREPAGECOMMITMENTEXTPROC)(GLuint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLboolean);
#endif
#if !defined(PFNGLTEXTUREPARAMETERFEXTPROC)
typedef void(*PFNGLTEXTUREPARAMETERFEXTPROC)(GLuint,GLenum,GLenum,GLfloat);
#endif
#if !defined(PFNGLTEXTUREPARAMETERFPROC)
typedef void(*PFNGLTEXTUREPARAMETERFPROC)(GLuint,GLenum,GLfloat);
#endif
#if !defined(PFNGLTEXTUREPARAMETERFVEXTPROC)
typedef void(*PFNGLTEXTUREPARAMETERFVEXTPROC)(GLuint,GLenum,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLTEXTUREPARAMETERFVPROC)
typedef void(*PFNGLTEXTUREPARAMETERFVPROC)(GLuint,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLTEXTUREPARAMETERIEXTPROC)
typedef void(*PFNGLTEXTUREPARAMETERIEXTPROC)(GLuint,GLenum,GLenum,GLint);
#endif
#if !defined(PFNGLTEXTUREPARAMETERIPROC)
typedef void(*PFNGLTEXTUREPARAMETERIPROC)(GLuint,GLenum,GLint);
#endif
#if !defined(PFNGLTEXTUREPARAMETERIIVEXTPROC)
typedef void(*PFNGLTEXTUREPARAMETERIIVEXTPROC)(GLuint,GLenum,GLenum,const GLint*);
#endif
#if !defined(PFNGLTEXTUREPARAMETERIIVPROC)
typedef void(*PFNGLTEXTUREPARAMETERIIVPROC)(GLuint,GLenum,const GLint*);
#endif
#if !defined(PFNGLTEXTUREPARAMETERIUIVEXTPROC)
typedef void(*PFNGLTEXTUREPARAMETERIUIVEXTPROC)(GLuint,GLenum,GLenum,const GLuint*);
#endif
#if !defined(PFNGLTEXTUREPARAMETERIUIVPROC)
typedef void(*PFNGLTEXTUREPARAMETERIUIVPROC)(GLuint,GLenum,const GLuint*);
#endif
#if !defined(PFNGLTEXTUREPARAMETERIVEXTPROC)
typedef void(*PFNGLTEXTUREPARAMETERIVEXTPROC)(GLuint,GLenum,GLenum,const GLint*);
#endif
#if !defined(PFNGLTEXTUREPARAMETERIVPROC)
typedef void(*PFNGLTEXTUREPARAMETERIVPROC)(GLuint,GLenum,const GLint*);
#endif
#if !defined(PFNGLTEXTURERANGEAPPLEPROC)
typedef void(*PFNGLTEXTURERANGEAPPLEPROC)(GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLTEXTURERENDERBUFFEREXTPROC)
typedef void(*PFNGLTEXTURERENDERBUFFEREXTPROC)(GLuint,GLenum,GLuint);
#endif
#if !defined(PFNGLTEXTURESTORAGE1DEXTPROC)
typedef void(*PFNGLTEXTURESTORAGE1DEXTPROC)(GLuint,GLenum,GLsizei,GLenum,GLsizei);
#endif
#if !defined(PFNGLTEXTURESTORAGE1DPROC)
typedef void(*PFNGLTEXTURESTORAGE1DPROC)(GLuint,GLsizei,GLenum,GLsizei);
#endif
#if !defined(PFNGLTEXTURESTORAGE2DEXTPROC)
typedef void(*PFNGLTEXTURESTORAGE2DEXTPROC)(GLuint,GLenum,GLsizei,GLenum,GLsizei,GLsizei);
#endif
#if !defined(PFNGLTEXTURESTORAGE2DPROC)
typedef void(*PFNGLTEXTURESTORAGE2DPROC)(GLuint,GLsizei,GLenum,GLsizei,GLsizei);
#endif
#if !defined(PFNGLTEXTURESTORAGE2DMULTISAMPLEEXTPROC)
typedef void(*PFNGLTEXTURESTORAGE2DMULTISAMPLEEXTPROC)(GLuint,GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLboolean);
#endif
#if !defined(PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC)
typedef void(*PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC)(GLuint,GLsizei,GLenum,GLsizei,GLsizei,GLboolean);
#endif
#if !defined(PFNGLTEXTURESTORAGE3DEXTPROC)
typedef void(*PFNGLTEXTURESTORAGE3DEXTPROC)(GLuint,GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei);
#endif
#if !defined(PFNGLTEXTURESTORAGE3DPROC)
typedef void(*PFNGLTEXTURESTORAGE3DPROC)(GLuint,GLsizei,GLenum,GLsizei,GLsizei,GLsizei);
#endif
#if !defined(PFNGLTEXTURESTORAGE3DMULTISAMPLEEXTPROC)
typedef void(*PFNGLTEXTURESTORAGE3DMULTISAMPLEEXTPROC)(GLuint,GLenum,GLsizei,GLenum,GLsizei,GLsizei,GLsizei,GLboolean);
#endif
#if !defined(PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC)
typedef void(*PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC)(GLuint,GLsizei,GLenum,GLsizei,GLsizei,GLsizei,GLboolean);
#endif
#if !defined(PFNGLTEXTURESTORAGESPARSEAMDPROC)
typedef void(*PFNGLTEXTURESTORAGESPARSEAMDPROC)(GLuint,GLenum,GLenum,GLsizei,GLsizei,GLsizei,GLsizei,GLbitfield);
#endif
#if !defined(PFNGLTEXTURESUBIMAGE1DEXTPROC)
typedef void(*PFNGLTEXTURESUBIMAGE1DEXTPROC)(GLuint,GLenum,GLint,GLint,GLsizei,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLTEXTURESUBIMAGE1DPROC)
typedef void(*PFNGLTEXTURESUBIMAGE1DPROC)(GLuint,GLint,GLint,GLsizei,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLTEXTURESUBIMAGE2DEXTPROC)
typedef void(*PFNGLTEXTURESUBIMAGE2DEXTPROC)(GLuint,GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLTEXTURESUBIMAGE2DPROC)
typedef void(*PFNGLTEXTURESUBIMAGE2DPROC)(GLuint,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLTEXTURESUBIMAGE3DEXTPROC)
typedef void(*PFNGLTEXTURESUBIMAGE3DEXTPROC)(GLuint,GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLTEXTURESUBIMAGE3DPROC)
typedef void(*PFNGLTEXTURESUBIMAGE3DPROC)(GLuint,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const void*);
#endif
#if !defined(PFNGLTEXTUREVIEWPROC)
typedef void(*PFNGLTEXTUREVIEWPROC)(GLuint,GLenum,GLuint,GLenum,GLuint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLTRACKMATRIXNVPROC)
typedef void(*PFNGLTRACKMATRIXNVPROC)(GLenum,GLuint,GLenum,GLenum);
#endif
#if !defined(PFNGLTRANSFORMFEEDBACKATTRIBSNVPROC)
typedef void(*PFNGLTRANSFORMFEEDBACKATTRIBSNVPROC)(GLsizei,const GLint*,GLenum);
#endif
#if !defined(PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC)
typedef void(*PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC)(GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC)
typedef void(*PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC)(GLuint,GLuint,GLuint,GLintptr,GLsizeiptr);
#endif
#if !defined(PFNGLTRANSFORMFEEDBACKSTREAMATTRIBSNVPROC)
typedef void(*PFNGLTRANSFORMFEEDBACKSTREAMATTRIBSNVPROC)(GLsizei,const GLint*,GLsizei,const GLint*,GLenum);
#endif
#if !defined(PFNGLTRANSFORMFEEDBACKVARYINGSEXTPROC)
typedef void(*PFNGLTRANSFORMFEEDBACKVARYINGSEXTPROC)(GLuint,GLsizei,const GLchar*const*,GLenum);
#endif
#if !defined(PFNGLTRANSFORMFEEDBACKVARYINGSPROC)
typedef void(*PFNGLTRANSFORMFEEDBACKVARYINGSPROC)(GLuint,GLsizei,const GLchar*const*,GLenum);
#endif
#if !defined(PFNGLTRANSFORMFEEDBACKVARYINGSNVPROC)
typedef void(*PFNGLTRANSFORMFEEDBACKVARYINGSNVPROC)(GLuint,GLsizei,const GLint*,GLenum);
#endif
#if !defined(PFNGLTRANSFORMPATHNVPROC)
typedef void(*PFNGLTRANSFORMPATHNVPROC)(GLuint,GLuint,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLTRANSLATEDPROC)
typedef void(*PFNGLTRANSLATEDPROC)(GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLTRANSLATEFPROC)
typedef void(*PFNGLTRANSLATEFPROC)(GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLTRANSLATEXOESPROC)
typedef void(*PFNGLTRANSLATEXOESPROC)(GLfixed,GLfixed,GLfixed);
#endif
#if !defined(PFNGLUNIFORM1DPROC)
typedef void(*PFNGLUNIFORM1DPROC)(GLint,GLdouble);
#endif
#if !defined(PFNGLUNIFORM1DVPROC)
typedef void(*PFNGLUNIFORM1DVPROC)(GLint,GLsizei,const GLdouble*);
#endif
#if !defined(PFNGLUNIFORM1FARBPROC)
typedef void(*PFNGLUNIFORM1FARBPROC)(GLint,GLfloat);
#endif
#if !defined(PFNGLUNIFORM1FPROC)
typedef void(*PFNGLUNIFORM1FPROC)(GLint,GLfloat);
#endif
#if !defined(PFNGLUNIFORM1FVARBPROC)
typedef void(*PFNGLUNIFORM1FVARBPROC)(GLint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLUNIFORM1FVPROC)
typedef void(*PFNGLUNIFORM1FVPROC)(GLint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLUNIFORM1I64ARBPROC)
typedef void(*PFNGLUNIFORM1I64ARBPROC)(GLint,GLint64);
#endif
#if !defined(PFNGLUNIFORM1I64NVPROC)
typedef void(*PFNGLUNIFORM1I64NVPROC)(GLint,GLint64EXT);
#endif
#if !defined(PFNGLUNIFORM1I64VARBPROC)
typedef void(*PFNGLUNIFORM1I64VARBPROC)(GLint,GLsizei,const GLint64*);
#endif
#if !defined(PFNGLUNIFORM1I64VNVPROC)
typedef void(*PFNGLUNIFORM1I64VNVPROC)(GLint,GLsizei,const GLint64EXT*);
#endif
#if !defined(PFNGLUNIFORM1IARBPROC)
typedef void(*PFNGLUNIFORM1IARBPROC)(GLint,GLint);
#endif
#if !defined(PFNGLUNIFORM1IPROC)
typedef void(*PFNGLUNIFORM1IPROC)(GLint,GLint);
#endif
#if !defined(PFNGLUNIFORM1IVARBPROC)
typedef void(*PFNGLUNIFORM1IVARBPROC)(GLint,GLsizei,const GLint*);
#endif
#if !defined(PFNGLUNIFORM1IVPROC)
typedef void(*PFNGLUNIFORM1IVPROC)(GLint,GLsizei,const GLint*);
#endif
#if !defined(PFNGLUNIFORM1UI64ARBPROC)
typedef void(*PFNGLUNIFORM1UI64ARBPROC)(GLint,GLuint64);
#endif
#if !defined(PFNGLUNIFORM1UI64NVPROC)
typedef void(*PFNGLUNIFORM1UI64NVPROC)(GLint,GLuint64EXT);
#endif
#if !defined(PFNGLUNIFORM1UI64VARBPROC)
typedef void(*PFNGLUNIFORM1UI64VARBPROC)(GLint,GLsizei,const GLuint64*);
#endif
#if !defined(PFNGLUNIFORM1UI64VNVPROC)
typedef void(*PFNGLUNIFORM1UI64VNVPROC)(GLint,GLsizei,const GLuint64EXT*);
#endif
#if !defined(PFNGLUNIFORM1UIEXTPROC)
typedef void(*PFNGLUNIFORM1UIEXTPROC)(GLint,GLuint);
#endif
#if !defined(PFNGLUNIFORM1UIPROC)
typedef void(*PFNGLUNIFORM1UIPROC)(GLint,GLuint);
#endif
#if !defined(PFNGLUNIFORM1UIVEXTPROC)
typedef void(*PFNGLUNIFORM1UIVEXTPROC)(GLint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLUNIFORM1UIVPROC)
typedef void(*PFNGLUNIFORM1UIVPROC)(GLint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLUNIFORM2DPROC)
typedef void(*PFNGLUNIFORM2DPROC)(GLint,GLdouble,GLdouble);
#endif
#if !defined(PFNGLUNIFORM2DVPROC)
typedef void(*PFNGLUNIFORM2DVPROC)(GLint,GLsizei,const GLdouble*);
#endif
#if !defined(PFNGLUNIFORM2FARBPROC)
typedef void(*PFNGLUNIFORM2FARBPROC)(GLint,GLfloat,GLfloat);
#endif
#if !defined(PFNGLUNIFORM2FPROC)
typedef void(*PFNGLUNIFORM2FPROC)(GLint,GLfloat,GLfloat);
#endif
#if !defined(PFNGLUNIFORM2FVARBPROC)
typedef void(*PFNGLUNIFORM2FVARBPROC)(GLint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLUNIFORM2FVPROC)
typedef void(*PFNGLUNIFORM2FVPROC)(GLint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLUNIFORM2I64ARBPROC)
typedef void(*PFNGLUNIFORM2I64ARBPROC)(GLint,GLint64,GLint64);
#endif
#if !defined(PFNGLUNIFORM2I64NVPROC)
typedef void(*PFNGLUNIFORM2I64NVPROC)(GLint,GLint64EXT,GLint64EXT);
#endif
#if !defined(PFNGLUNIFORM2I64VARBPROC)
typedef void(*PFNGLUNIFORM2I64VARBPROC)(GLint,GLsizei,const GLint64*);
#endif
#if !defined(PFNGLUNIFORM2I64VNVPROC)
typedef void(*PFNGLUNIFORM2I64VNVPROC)(GLint,GLsizei,const GLint64EXT*);
#endif
#if !defined(PFNGLUNIFORM2IARBPROC)
typedef void(*PFNGLUNIFORM2IARBPROC)(GLint,GLint,GLint);
#endif
#if !defined(PFNGLUNIFORM2IPROC)
typedef void(*PFNGLUNIFORM2IPROC)(GLint,GLint,GLint);
#endif
#if !defined(PFNGLUNIFORM2IVARBPROC)
typedef void(*PFNGLUNIFORM2IVARBPROC)(GLint,GLsizei,const GLint*);
#endif
#if !defined(PFNGLUNIFORM2IVPROC)
typedef void(*PFNGLUNIFORM2IVPROC)(GLint,GLsizei,const GLint*);
#endif
#if !defined(PFNGLUNIFORM2UI64ARBPROC)
typedef void(*PFNGLUNIFORM2UI64ARBPROC)(GLint,GLuint64,GLuint64);
#endif
#if !defined(PFNGLUNIFORM2UI64NVPROC)
typedef void(*PFNGLUNIFORM2UI64NVPROC)(GLint,GLuint64EXT,GLuint64EXT);
#endif
#if !defined(PFNGLUNIFORM2UI64VARBPROC)
typedef void(*PFNGLUNIFORM2UI64VARBPROC)(GLint,GLsizei,const GLuint64*);
#endif
#if !defined(PFNGLUNIFORM2UI64VNVPROC)
typedef void(*PFNGLUNIFORM2UI64VNVPROC)(GLint,GLsizei,const GLuint64EXT*);
#endif
#if !defined(PFNGLUNIFORM2UIEXTPROC)
typedef void(*PFNGLUNIFORM2UIEXTPROC)(GLint,GLuint,GLuint);
#endif
#if !defined(PFNGLUNIFORM2UIPROC)
typedef void(*PFNGLUNIFORM2UIPROC)(GLint,GLuint,GLuint);
#endif
#if !defined(PFNGLUNIFORM2UIVEXTPROC)
typedef void(*PFNGLUNIFORM2UIVEXTPROC)(GLint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLUNIFORM2UIVPROC)
typedef void(*PFNGLUNIFORM2UIVPROC)(GLint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLUNIFORM3DPROC)
typedef void(*PFNGLUNIFORM3DPROC)(GLint,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLUNIFORM3DVPROC)
typedef void(*PFNGLUNIFORM3DVPROC)(GLint,GLsizei,const GLdouble*);
#endif
#if !defined(PFNGLUNIFORM3FARBPROC)
typedef void(*PFNGLUNIFORM3FARBPROC)(GLint,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLUNIFORM3FPROC)
typedef void(*PFNGLUNIFORM3FPROC)(GLint,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLUNIFORM3FVARBPROC)
typedef void(*PFNGLUNIFORM3FVARBPROC)(GLint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLUNIFORM3FVPROC)
typedef void(*PFNGLUNIFORM3FVPROC)(GLint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLUNIFORM3I64ARBPROC)
typedef void(*PFNGLUNIFORM3I64ARBPROC)(GLint,GLint64,GLint64,GLint64);
#endif
#if !defined(PFNGLUNIFORM3I64NVPROC)
typedef void(*PFNGLUNIFORM3I64NVPROC)(GLint,GLint64EXT,GLint64EXT,GLint64EXT);
#endif
#if !defined(PFNGLUNIFORM3I64VARBPROC)
typedef void(*PFNGLUNIFORM3I64VARBPROC)(GLint,GLsizei,const GLint64*);
#endif
#if !defined(PFNGLUNIFORM3I64VNVPROC)
typedef void(*PFNGLUNIFORM3I64VNVPROC)(GLint,GLsizei,const GLint64EXT*);
#endif
#if !defined(PFNGLUNIFORM3IARBPROC)
typedef void(*PFNGLUNIFORM3IARBPROC)(GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLUNIFORM3IPROC)
typedef void(*PFNGLUNIFORM3IPROC)(GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLUNIFORM3IVARBPROC)
typedef void(*PFNGLUNIFORM3IVARBPROC)(GLint,GLsizei,const GLint*);
#endif
#if !defined(PFNGLUNIFORM3IVPROC)
typedef void(*PFNGLUNIFORM3IVPROC)(GLint,GLsizei,const GLint*);
#endif
#if !defined(PFNGLUNIFORM3UI64ARBPROC)
typedef void(*PFNGLUNIFORM3UI64ARBPROC)(GLint,GLuint64,GLuint64,GLuint64);
#endif
#if !defined(PFNGLUNIFORM3UI64NVPROC)
typedef void(*PFNGLUNIFORM3UI64NVPROC)(GLint,GLuint64EXT,GLuint64EXT,GLuint64EXT);
#endif
#if !defined(PFNGLUNIFORM3UI64VARBPROC)
typedef void(*PFNGLUNIFORM3UI64VARBPROC)(GLint,GLsizei,const GLuint64*);
#endif
#if !defined(PFNGLUNIFORM3UI64VNVPROC)
typedef void(*PFNGLUNIFORM3UI64VNVPROC)(GLint,GLsizei,const GLuint64EXT*);
#endif
#if !defined(PFNGLUNIFORM3UIEXTPROC)
typedef void(*PFNGLUNIFORM3UIEXTPROC)(GLint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLUNIFORM3UIPROC)
typedef void(*PFNGLUNIFORM3UIPROC)(GLint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLUNIFORM3UIVEXTPROC)
typedef void(*PFNGLUNIFORM3UIVEXTPROC)(GLint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLUNIFORM3UIVPROC)
typedef void(*PFNGLUNIFORM3UIVPROC)(GLint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLUNIFORM4DPROC)
typedef void(*PFNGLUNIFORM4DPROC)(GLint,GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLUNIFORM4DVPROC)
typedef void(*PFNGLUNIFORM4DVPROC)(GLint,GLsizei,const GLdouble*);
#endif
#if !defined(PFNGLUNIFORM4FARBPROC)
typedef void(*PFNGLUNIFORM4FARBPROC)(GLint,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLUNIFORM4FPROC)
typedef void(*PFNGLUNIFORM4FPROC)(GLint,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLUNIFORM4FVARBPROC)
typedef void(*PFNGLUNIFORM4FVARBPROC)(GLint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLUNIFORM4FVPROC)
typedef void(*PFNGLUNIFORM4FVPROC)(GLint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLUNIFORM4I64ARBPROC)
typedef void(*PFNGLUNIFORM4I64ARBPROC)(GLint,GLint64,GLint64,GLint64,GLint64);
#endif
#if !defined(PFNGLUNIFORM4I64NVPROC)
typedef void(*PFNGLUNIFORM4I64NVPROC)(GLint,GLint64EXT,GLint64EXT,GLint64EXT,GLint64EXT);
#endif
#if !defined(PFNGLUNIFORM4I64VARBPROC)
typedef void(*PFNGLUNIFORM4I64VARBPROC)(GLint,GLsizei,const GLint64*);
#endif
#if !defined(PFNGLUNIFORM4I64VNVPROC)
typedef void(*PFNGLUNIFORM4I64VNVPROC)(GLint,GLsizei,const GLint64EXT*);
#endif
#if !defined(PFNGLUNIFORM4IARBPROC)
typedef void(*PFNGLUNIFORM4IARBPROC)(GLint,GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLUNIFORM4IPROC)
typedef void(*PFNGLUNIFORM4IPROC)(GLint,GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLUNIFORM4IVARBPROC)
typedef void(*PFNGLUNIFORM4IVARBPROC)(GLint,GLsizei,const GLint*);
#endif
#if !defined(PFNGLUNIFORM4IVPROC)
typedef void(*PFNGLUNIFORM4IVPROC)(GLint,GLsizei,const GLint*);
#endif
#if !defined(PFNGLUNIFORM4UI64ARBPROC)
typedef void(*PFNGLUNIFORM4UI64ARBPROC)(GLint,GLuint64,GLuint64,GLuint64,GLuint64);
#endif
#if !defined(PFNGLUNIFORM4UI64NVPROC)
typedef void(*PFNGLUNIFORM4UI64NVPROC)(GLint,GLuint64EXT,GLuint64EXT,GLuint64EXT,GLuint64EXT);
#endif
#if !defined(PFNGLUNIFORM4UI64VARBPROC)
typedef void(*PFNGLUNIFORM4UI64VARBPROC)(GLint,GLsizei,const GLuint64*);
#endif
#if !defined(PFNGLUNIFORM4UI64VNVPROC)
typedef void(*PFNGLUNIFORM4UI64VNVPROC)(GLint,GLsizei,const GLuint64EXT*);
#endif
#if !defined(PFNGLUNIFORM4UIEXTPROC)
typedef void(*PFNGLUNIFORM4UIEXTPROC)(GLint,GLuint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLUNIFORM4UIPROC)
typedef void(*PFNGLUNIFORM4UIPROC)(GLint,GLuint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLUNIFORM4UIVEXTPROC)
typedef void(*PFNGLUNIFORM4UIVEXTPROC)(GLint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLUNIFORM4UIVPROC)
typedef void(*PFNGLUNIFORM4UIVPROC)(GLint,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLUNIFORMBLOCKBINDINGPROC)
typedef void(*PFNGLUNIFORMBLOCKBINDINGPROC)(GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLUNIFORMBUFFEREXTPROC)
typedef void(*PFNGLUNIFORMBUFFEREXTPROC)(GLuint,GLint,GLuint);
#endif
#if !defined(PFNGLUNIFORMHANDLEUI64ARBPROC)
typedef void(*PFNGLUNIFORMHANDLEUI64ARBPROC)(GLint,GLuint64);
#endif
#if !defined(PFNGLUNIFORMHANDLEUI64NVPROC)
typedef void(*PFNGLUNIFORMHANDLEUI64NVPROC)(GLint,GLuint64);
#endif
#if !defined(PFNGLUNIFORMHANDLEUI64VARBPROC)
typedef void(*PFNGLUNIFORMHANDLEUI64VARBPROC)(GLint,GLsizei,const GLuint64*);
#endif
#if !defined(PFNGLUNIFORMHANDLEUI64VNVPROC)
typedef void(*PFNGLUNIFORMHANDLEUI64VNVPROC)(GLint,GLsizei,const GLuint64*);
#endif
#if !defined(PFNGLUNIFORMMATRIX2DVPROC)
typedef void(*PFNGLUNIFORMMATRIX2DVPROC)(GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLUNIFORMMATRIX2FVARBPROC)
typedef void(*PFNGLUNIFORMMATRIX2FVARBPROC)(GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLUNIFORMMATRIX2FVPROC)
typedef void(*PFNGLUNIFORMMATRIX2FVPROC)(GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLUNIFORMMATRIX2X3DVPROC)
typedef void(*PFNGLUNIFORMMATRIX2X3DVPROC)(GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLUNIFORMMATRIX2X3FVPROC)
typedef void(*PFNGLUNIFORMMATRIX2X3FVPROC)(GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLUNIFORMMATRIX2X4DVPROC)
typedef void(*PFNGLUNIFORMMATRIX2X4DVPROC)(GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLUNIFORMMATRIX2X4FVPROC)
typedef void(*PFNGLUNIFORMMATRIX2X4FVPROC)(GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLUNIFORMMATRIX3DVPROC)
typedef void(*PFNGLUNIFORMMATRIX3DVPROC)(GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLUNIFORMMATRIX3FVARBPROC)
typedef void(*PFNGLUNIFORMMATRIX3FVARBPROC)(GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLUNIFORMMATRIX3FVPROC)
typedef void(*PFNGLUNIFORMMATRIX3FVPROC)(GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLUNIFORMMATRIX3X2DVPROC)
typedef void(*PFNGLUNIFORMMATRIX3X2DVPROC)(GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLUNIFORMMATRIX3X2FVPROC)
typedef void(*PFNGLUNIFORMMATRIX3X2FVPROC)(GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLUNIFORMMATRIX3X4DVPROC)
typedef void(*PFNGLUNIFORMMATRIX3X4DVPROC)(GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLUNIFORMMATRIX3X4FVPROC)
typedef void(*PFNGLUNIFORMMATRIX3X4FVPROC)(GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLUNIFORMMATRIX4DVPROC)
typedef void(*PFNGLUNIFORMMATRIX4DVPROC)(GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLUNIFORMMATRIX4FVARBPROC)
typedef void(*PFNGLUNIFORMMATRIX4FVARBPROC)(GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLUNIFORMMATRIX4FVPROC)
typedef void(*PFNGLUNIFORMMATRIX4FVPROC)(GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLUNIFORMMATRIX4X2DVPROC)
typedef void(*PFNGLUNIFORMMATRIX4X2DVPROC)(GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLUNIFORMMATRIX4X2FVPROC)
typedef void(*PFNGLUNIFORMMATRIX4X2FVPROC)(GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLUNIFORMMATRIX4X3DVPROC)
typedef void(*PFNGLUNIFORMMATRIX4X3DVPROC)(GLint,GLsizei,GLboolean,const GLdouble*);
#endif
#if !defined(PFNGLUNIFORMMATRIX4X3FVPROC)
typedef void(*PFNGLUNIFORMMATRIX4X3FVPROC)(GLint,GLsizei,GLboolean,const GLfloat*);
#endif
#if !defined(PFNGLUNIFORMSUBROUTINESUIVPROC)
typedef void(*PFNGLUNIFORMSUBROUTINESUIVPROC)(GLenum,GLsizei,const GLuint*);
#endif
#if !defined(PFNGLUNIFORMUI64NVPROC)
typedef void(*PFNGLUNIFORMUI64NVPROC)(GLint,GLuint64EXT);
#endif
#if !defined(PFNGLUNIFORMUI64VNVPROC)
typedef void(*PFNGLUNIFORMUI64VNVPROC)(GLint,GLsizei,const GLuint64EXT*);
#endif
#if !defined(PFNGLUNLOCKARRAYSEXTPROC)
typedef void(*PFNGLUNLOCKARRAYSEXTPROC)();
#endif
#if !defined(PFNGLUNMAPOBJECTBUFFERATIPROC)
typedef void(*PFNGLUNMAPOBJECTBUFFERATIPROC)(GLuint);
#endif
#if !defined(PFNGLUNMAPTEXTURE2DINTELPROC)
typedef void(*PFNGLUNMAPTEXTURE2DINTELPROC)(GLuint,GLint);
#endif
#if !defined(PFNGLUPDATEOBJECTBUFFERATIPROC)
typedef void(*PFNGLUPDATEOBJECTBUFFERATIPROC)(GLuint,GLuint,GLsizei,const void*,GLenum);
#endif
#if !defined(PFNGLUSEPROGRAMPROC)
typedef void(*PFNGLUSEPROGRAMPROC)(GLuint);
#endif
#if !defined(PFNGLUSEPROGRAMOBJECTARBPROC)
typedef void(*PFNGLUSEPROGRAMOBJECTARBPROC)(GLhandleARB);
#endif
#if !defined(PFNGLUSEPROGRAMSTAGESPROC)
typedef void(*PFNGLUSEPROGRAMSTAGESPROC)(GLuint,GLbitfield,GLuint);
#endif
#if !defined(PFNGLUSESHADERPROGRAMEXTPROC)
typedef void(*PFNGLUSESHADERPROGRAMEXTPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLVALIDATEPROGRAMARBPROC)
typedef void(*PFNGLVALIDATEPROGRAMARBPROC)(GLhandleARB);
#endif
#if !defined(PFNGLVALIDATEPROGRAMPROC)
typedef void(*PFNGLVALIDATEPROGRAMPROC)(GLuint);
#endif
#if !defined(PFNGLVALIDATEPROGRAMPIPELINEPROC)
typedef void(*PFNGLVALIDATEPROGRAMPIPELINEPROC)(GLuint);
#endif
#if !defined(PFNGLVARIANTARRAYOBJECTATIPROC)
typedef void(*PFNGLVARIANTARRAYOBJECTATIPROC)(GLuint,GLenum,GLsizei,GLuint,GLuint);
#endif
#if !defined(PFNGLVARIANTBVEXTPROC)
typedef void(*PFNGLVARIANTBVEXTPROC)(GLuint,const GLbyte*);
#endif
#if !defined(PFNGLVARIANTDVEXTPROC)
typedef void(*PFNGLVARIANTDVEXTPROC)(GLuint,const GLdouble*);
#endif
#if !defined(PFNGLVARIANTFVEXTPROC)
typedef void(*PFNGLVARIANTFVEXTPROC)(GLuint,const GLfloat*);
#endif
#if !defined(PFNGLVARIANTIVEXTPROC)
typedef void(*PFNGLVARIANTIVEXTPROC)(GLuint,const GLint*);
#endif
#if !defined(PFNGLVARIANTPOINTEREXTPROC)
typedef void(*PFNGLVARIANTPOINTEREXTPROC)(GLuint,GLenum,GLuint,const void*);
#endif
#if !defined(PFNGLVARIANTSVEXTPROC)
typedef void(*PFNGLVARIANTSVEXTPROC)(GLuint,const GLshort*);
#endif
#if !defined(PFNGLVARIANTUBVEXTPROC)
typedef void(*PFNGLVARIANTUBVEXTPROC)(GLuint,const GLubyte*);
#endif
#if !defined(PFNGLVARIANTUIVEXTPROC)
typedef void(*PFNGLVARIANTUIVEXTPROC)(GLuint,const GLuint*);
#endif
#if !defined(PFNGLVARIANTUSVEXTPROC)
typedef void(*PFNGLVARIANTUSVEXTPROC)(GLuint,const GLushort*);
#endif
#if !defined(PFNGLVDPAUFININVPROC)
typedef void(*PFNGLVDPAUFININVPROC)();
#endif
#if !defined(PFNGLVDPAUGETSURFACEIVNVPROC)
typedef void(*PFNGLVDPAUGETSURFACEIVNVPROC)(GLvdpauSurfaceNV,GLenum,GLsizei,GLsizei*,GLint*);
#endif
#if !defined(PFNGLVDPAUINITNVPROC)
typedef void(*PFNGLVDPAUINITNVPROC)(const void*,const void*);
#endif
#if !defined(PFNGLVDPAUMAPSURFACESNVPROC)
typedef void(*PFNGLVDPAUMAPSURFACESNVPROC)(GLsizei,const GLvdpauSurfaceNV*);
#endif
#if !defined(PFNGLVDPAUSURFACEACCESSNVPROC)
typedef void(*PFNGLVDPAUSURFACEACCESSNVPROC)(GLvdpauSurfaceNV,GLenum);
#endif
#if !defined(PFNGLVDPAUUNMAPSURFACESNVPROC)
typedef void(*PFNGLVDPAUUNMAPSURFACESNVPROC)(GLsizei,const GLvdpauSurfaceNV*);
#endif
#if !defined(PFNGLVDPAUUNREGISTERSURFACENVPROC)
typedef void(*PFNGLVDPAUUNREGISTERSURFACENVPROC)(GLvdpauSurfaceNV);
#endif
#if !defined(PFNGLVERTEX2BOESPROC)
typedef void(*PFNGLVERTEX2BOESPROC)(GLbyte,GLbyte);
#endif
#if !defined(PFNGLVERTEX2BVOESPROC)
typedef void(*PFNGLVERTEX2BVOESPROC)(const GLbyte*);
#endif
#if !defined(PFNGLVERTEX2DPROC)
typedef void(*PFNGLVERTEX2DPROC)(GLdouble,GLdouble);
#endif
#if !defined(PFNGLVERTEX2DVPROC)
typedef void(*PFNGLVERTEX2DVPROC)(const GLdouble*);
#endif
#if !defined(PFNGLVERTEX2FPROC)
typedef void(*PFNGLVERTEX2FPROC)(GLfloat,GLfloat);
#endif
#if !defined(PFNGLVERTEX2FVPROC)
typedef void(*PFNGLVERTEX2FVPROC)(const GLfloat*);
#endif
#if !defined(PFNGLVERTEX2HNVPROC)
typedef void(*PFNGLVERTEX2HNVPROC)(GLhalfNV,GLhalfNV);
#endif
#if !defined(PFNGLVERTEX2HVNVPROC)
typedef void(*PFNGLVERTEX2HVNVPROC)(const GLhalfNV*);
#endif
#if !defined(PFNGLVERTEX2IPROC)
typedef void(*PFNGLVERTEX2IPROC)(GLint,GLint);
#endif
#if !defined(PFNGLVERTEX2IVPROC)
typedef void(*PFNGLVERTEX2IVPROC)(const GLint*);
#endif
#if !defined(PFNGLVERTEX2SPROC)
typedef void(*PFNGLVERTEX2SPROC)(GLshort,GLshort);
#endif
#if !defined(PFNGLVERTEX2SVPROC)
typedef void(*PFNGLVERTEX2SVPROC)(const GLshort*);
#endif
#if !defined(PFNGLVERTEX2XOESPROC)
typedef void(*PFNGLVERTEX2XOESPROC)(GLfixed);
#endif
#if !defined(PFNGLVERTEX2XVOESPROC)
typedef void(*PFNGLVERTEX2XVOESPROC)(const GLfixed*);
#endif
#if !defined(PFNGLVERTEX3BOESPROC)
typedef void(*PFNGLVERTEX3BOESPROC)(GLbyte,GLbyte,GLbyte);
#endif
#if !defined(PFNGLVERTEX3BVOESPROC)
typedef void(*PFNGLVERTEX3BVOESPROC)(const GLbyte*);
#endif
#if !defined(PFNGLVERTEX3DPROC)
typedef void(*PFNGLVERTEX3DPROC)(GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLVERTEX3DVPROC)
typedef void(*PFNGLVERTEX3DVPROC)(const GLdouble*);
#endif
#if !defined(PFNGLVERTEX3FPROC)
typedef void(*PFNGLVERTEX3FPROC)(GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLVERTEX3FVPROC)
typedef void(*PFNGLVERTEX3FVPROC)(const GLfloat*);
#endif
#if !defined(PFNGLVERTEX3HNVPROC)
typedef void(*PFNGLVERTEX3HNVPROC)(GLhalfNV,GLhalfNV,GLhalfNV);
#endif
#if !defined(PFNGLVERTEX3HVNVPROC)
typedef void(*PFNGLVERTEX3HVNVPROC)(const GLhalfNV*);
#endif
#if !defined(PFNGLVERTEX3IPROC)
typedef void(*PFNGLVERTEX3IPROC)(GLint,GLint,GLint);
#endif
#if !defined(PFNGLVERTEX3IVPROC)
typedef void(*PFNGLVERTEX3IVPROC)(const GLint*);
#endif
#if !defined(PFNGLVERTEX3SPROC)
typedef void(*PFNGLVERTEX3SPROC)(GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLVERTEX3SVPROC)
typedef void(*PFNGLVERTEX3SVPROC)(const GLshort*);
#endif
#if !defined(PFNGLVERTEX3XOESPROC)
typedef void(*PFNGLVERTEX3XOESPROC)(GLfixed,GLfixed);
#endif
#if !defined(PFNGLVERTEX3XVOESPROC)
typedef void(*PFNGLVERTEX3XVOESPROC)(const GLfixed*);
#endif
#if !defined(PFNGLVERTEX4BOESPROC)
typedef void(*PFNGLVERTEX4BOESPROC)(GLbyte,GLbyte,GLbyte,GLbyte);
#endif
#if !defined(PFNGLVERTEX4BVOESPROC)
typedef void(*PFNGLVERTEX4BVOESPROC)(const GLbyte*);
#endif
#if !defined(PFNGLVERTEX4DPROC)
typedef void(*PFNGLVERTEX4DPROC)(GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLVERTEX4DVPROC)
typedef void(*PFNGLVERTEX4DVPROC)(const GLdouble*);
#endif
#if !defined(PFNGLVERTEX4FPROC)
typedef void(*PFNGLVERTEX4FPROC)(GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLVERTEX4FVPROC)
typedef void(*PFNGLVERTEX4FVPROC)(const GLfloat*);
#endif
#if !defined(PFNGLVERTEX4HNVPROC)
typedef void(*PFNGLVERTEX4HNVPROC)(GLhalfNV,GLhalfNV,GLhalfNV,GLhalfNV);
#endif
#if !defined(PFNGLVERTEX4HVNVPROC)
typedef void(*PFNGLVERTEX4HVNVPROC)(const GLhalfNV*);
#endif
#if !defined(PFNGLVERTEX4IPROC)
typedef void(*PFNGLVERTEX4IPROC)(GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLVERTEX4IVPROC)
typedef void(*PFNGLVERTEX4IVPROC)(const GLint*);
#endif
#if !defined(PFNGLVERTEX4SPROC)
typedef void(*PFNGLVERTEX4SPROC)(GLshort,GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLVERTEX4SVPROC)
typedef void(*PFNGLVERTEX4SVPROC)(const GLshort*);
#endif
#if !defined(PFNGLVERTEX4XOESPROC)
typedef void(*PFNGLVERTEX4XOESPROC)(GLfixed,GLfixed,GLfixed);
#endif
#if !defined(PFNGLVERTEX4XVOESPROC)
typedef void(*PFNGLVERTEX4XVOESPROC)(const GLfixed*);
#endif
#if !defined(PFNGLVERTEXARRAYATTRIBBINDINGPROC)
typedef void(*PFNGLVERTEXARRAYATTRIBBINDINGPROC)(GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLVERTEXARRAYATTRIBFORMATPROC)
typedef void(*PFNGLVERTEXARRAYATTRIBFORMATPROC)(GLuint,GLuint,GLint,GLenum,GLboolean,GLuint);
#endif
#if !defined(PFNGLVERTEXARRAYATTRIBIFORMATPROC)
typedef void(*PFNGLVERTEXARRAYATTRIBIFORMATPROC)(GLuint,GLuint,GLint,GLenum,GLuint);
#endif
#if !defined(PFNGLVERTEXARRAYATTRIBLFORMATPROC)
typedef void(*PFNGLVERTEXARRAYATTRIBLFORMATPROC)(GLuint,GLuint,GLint,GLenum,GLuint);
#endif
#if !defined(PFNGLVERTEXARRAYBINDINGDIVISORPROC)
typedef void(*PFNGLVERTEXARRAYBINDINGDIVISORPROC)(GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLVERTEXARRAYBINDVERTEXBUFFEREXTPROC)
typedef void(*PFNGLVERTEXARRAYBINDVERTEXBUFFEREXTPROC)(GLuint,GLuint,GLuint,GLintptr,GLsizei);
#endif
#if !defined(PFNGLVERTEXARRAYCOLOROFFSETEXTPROC)
typedef void(*PFNGLVERTEXARRAYCOLOROFFSETEXTPROC)(GLuint,GLuint,GLint,GLenum,GLsizei,GLintptr);
#endif
#if !defined(PFNGLVERTEXARRAYEDGEFLAGOFFSETEXTPROC)
typedef void(*PFNGLVERTEXARRAYEDGEFLAGOFFSETEXTPROC)(GLuint,GLuint,GLsizei,GLintptr);
#endif
#if !defined(PFNGLVERTEXARRAYELEMENTBUFFERPROC)
typedef void(*PFNGLVERTEXARRAYELEMENTBUFFERPROC)(GLuint,GLuint);
#endif
#if !defined(PFNGLVERTEXARRAYFOGCOORDOFFSETEXTPROC)
typedef void(*PFNGLVERTEXARRAYFOGCOORDOFFSETEXTPROC)(GLuint,GLuint,GLenum,GLsizei,GLintptr);
#endif
#if !defined(PFNGLVERTEXARRAYINDEXOFFSETEXTPROC)
typedef void(*PFNGLVERTEXARRAYINDEXOFFSETEXTPROC)(GLuint,GLuint,GLenum,GLsizei,GLintptr);
#endif
#if !defined(PFNGLVERTEXARRAYMULTITEXCOORDOFFSETEXTPROC)
typedef void(*PFNGLVERTEXARRAYMULTITEXCOORDOFFSETEXTPROC)(GLuint,GLuint,GLenum,GLint,GLenum,GLsizei,GLintptr);
#endif
#if !defined(PFNGLVERTEXARRAYNORMALOFFSETEXTPROC)
typedef void(*PFNGLVERTEXARRAYNORMALOFFSETEXTPROC)(GLuint,GLuint,GLenum,GLsizei,GLintptr);
#endif
#if !defined(PFNGLVERTEXARRAYPARAMETERIAPPLEPROC)
typedef void(*PFNGLVERTEXARRAYPARAMETERIAPPLEPROC)(GLenum,GLint);
#endif
#if !defined(PFNGLVERTEXARRAYRANGEAPPLEPROC)
typedef void(*PFNGLVERTEXARRAYRANGEAPPLEPROC)(GLsizei,void*);
#endif
#if !defined(PFNGLVERTEXARRAYRANGENVPROC)
typedef void(*PFNGLVERTEXARRAYRANGENVPROC)(GLsizei,const void*);
#endif
#if !defined(PFNGLVERTEXARRAYSECONDARYCOLOROFFSETEXTPROC)
typedef void(*PFNGLVERTEXARRAYSECONDARYCOLOROFFSETEXTPROC)(GLuint,GLuint,GLint,GLenum,GLsizei,GLintptr);
#endif
#if !defined(PFNGLVERTEXARRAYTEXCOORDOFFSETEXTPROC)
typedef void(*PFNGLVERTEXARRAYTEXCOORDOFFSETEXTPROC)(GLuint,GLuint,GLint,GLenum,GLsizei,GLintptr);
#endif
#if !defined(PFNGLVERTEXARRAYVERTEXATTRIBBINDINGEXTPROC)
typedef void(*PFNGLVERTEXARRAYVERTEXATTRIBBINDINGEXTPROC)(GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLVERTEXARRAYVERTEXATTRIBDIVISOREXTPROC)
typedef void(*PFNGLVERTEXARRAYVERTEXATTRIBDIVISOREXTPROC)(GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLVERTEXARRAYVERTEXATTRIBFORMATEXTPROC)
typedef void(*PFNGLVERTEXARRAYVERTEXATTRIBFORMATEXTPROC)(GLuint,GLuint,GLint,GLenum,GLboolean,GLuint);
#endif
#if !defined(PFNGLVERTEXARRAYVERTEXATTRIBIFORMATEXTPROC)
typedef void(*PFNGLVERTEXARRAYVERTEXATTRIBIFORMATEXTPROC)(GLuint,GLuint,GLint,GLenum,GLuint);
#endif
#if !defined(PFNGLVERTEXARRAYVERTEXATTRIBIOFFSETEXTPROC)
typedef void(*PFNGLVERTEXARRAYVERTEXATTRIBIOFFSETEXTPROC)(GLuint,GLuint,GLuint,GLint,GLenum,GLsizei,GLintptr);
#endif
#if !defined(PFNGLVERTEXARRAYVERTEXATTRIBLFORMATEXTPROC)
typedef void(*PFNGLVERTEXARRAYVERTEXATTRIBLFORMATEXTPROC)(GLuint,GLuint,GLint,GLenum,GLuint);
#endif
#if !defined(PFNGLVERTEXARRAYVERTEXATTRIBLOFFSETEXTPROC)
typedef void(*PFNGLVERTEXARRAYVERTEXATTRIBLOFFSETEXTPROC)(GLuint,GLuint,GLuint,GLint,GLenum,GLsizei,GLintptr);
#endif
#if !defined(PFNGLVERTEXARRAYVERTEXATTRIBOFFSETEXTPROC)
typedef void(*PFNGLVERTEXARRAYVERTEXATTRIBOFFSETEXTPROC)(GLuint,GLuint,GLuint,GLint,GLenum,GLboolean,GLsizei,GLintptr);
#endif
#if !defined(PFNGLVERTEXARRAYVERTEXBINDINGDIVISOREXTPROC)
typedef void(*PFNGLVERTEXARRAYVERTEXBINDINGDIVISOREXTPROC)(GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLVERTEXARRAYVERTEXBUFFERPROC)
typedef void(*PFNGLVERTEXARRAYVERTEXBUFFERPROC)(GLuint,GLuint,GLuint,GLintptr,GLsizei);
#endif
#if !defined(PFNGLVERTEXARRAYVERTEXBUFFERSPROC)
typedef void(*PFNGLVERTEXARRAYVERTEXBUFFERSPROC)(GLuint,GLuint,GLsizei,const GLuint*,const GLintptr*,const GLsizei*);
#endif
#if !defined(PFNGLVERTEXARRAYVERTEXOFFSETEXTPROC)
typedef void(*PFNGLVERTEXARRAYVERTEXOFFSETEXTPROC)(GLuint,GLuint,GLint,GLenum,GLsizei,GLintptr);
#endif
#if !defined(PFNGLVERTEXATTRIB1DARBPROC)
typedef void(*PFNGLVERTEXATTRIB1DARBPROC)(GLuint,GLdouble);
#endif
#if !defined(PFNGLVERTEXATTRIB1DPROC)
typedef void(*PFNGLVERTEXATTRIB1DPROC)(GLuint,GLdouble);
#endif
#if !defined(PFNGLVERTEXATTRIB1DNVPROC)
typedef void(*PFNGLVERTEXATTRIB1DNVPROC)(GLuint,GLdouble);
#endif
#if !defined(PFNGLVERTEXATTRIB1DVARBPROC)
typedef void(*PFNGLVERTEXATTRIB1DVARBPROC)(GLuint,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIB1DVPROC)
typedef void(*PFNGLVERTEXATTRIB1DVPROC)(GLuint,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIB1DVNVPROC)
typedef void(*PFNGLVERTEXATTRIB1DVNVPROC)(GLuint,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIB1FARBPROC)
typedef void(*PFNGLVERTEXATTRIB1FARBPROC)(GLuint,GLfloat);
#endif
#if !defined(PFNGLVERTEXATTRIB1FPROC)
typedef void(*PFNGLVERTEXATTRIB1FPROC)(GLuint,GLfloat);
#endif
#if !defined(PFNGLVERTEXATTRIB1FNVPROC)
typedef void(*PFNGLVERTEXATTRIB1FNVPROC)(GLuint,GLfloat);
#endif
#if !defined(PFNGLVERTEXATTRIB1FVARBPROC)
typedef void(*PFNGLVERTEXATTRIB1FVARBPROC)(GLuint,const GLfloat*);
#endif
#if !defined(PFNGLVERTEXATTRIB1FVPROC)
typedef void(*PFNGLVERTEXATTRIB1FVPROC)(GLuint,const GLfloat*);
#endif
#if !defined(PFNGLVERTEXATTRIB1FVNVPROC)
typedef void(*PFNGLVERTEXATTRIB1FVNVPROC)(GLuint,const GLfloat*);
#endif
#if !defined(PFNGLVERTEXATTRIB1HNVPROC)
typedef void(*PFNGLVERTEXATTRIB1HNVPROC)(GLuint,GLhalfNV);
#endif
#if !defined(PFNGLVERTEXATTRIB1HVNVPROC)
typedef void(*PFNGLVERTEXATTRIB1HVNVPROC)(GLuint,const GLhalfNV*);
#endif
#if !defined(PFNGLVERTEXATTRIB1SARBPROC)
typedef void(*PFNGLVERTEXATTRIB1SARBPROC)(GLuint,GLshort);
#endif
#if !defined(PFNGLVERTEXATTRIB1SPROC)
typedef void(*PFNGLVERTEXATTRIB1SPROC)(GLuint,GLshort);
#endif
#if !defined(PFNGLVERTEXATTRIB1SNVPROC)
typedef void(*PFNGLVERTEXATTRIB1SNVPROC)(GLuint,GLshort);
#endif
#if !defined(PFNGLVERTEXATTRIB1SVARBPROC)
typedef void(*PFNGLVERTEXATTRIB1SVARBPROC)(GLuint,const GLshort*);
#endif
#if !defined(PFNGLVERTEXATTRIB1SVPROC)
typedef void(*PFNGLVERTEXATTRIB1SVPROC)(GLuint,const GLshort*);
#endif
#if !defined(PFNGLVERTEXATTRIB1SVNVPROC)
typedef void(*PFNGLVERTEXATTRIB1SVNVPROC)(GLuint,const GLshort*);
#endif
#if !defined(PFNGLVERTEXATTRIB2DARBPROC)
typedef void(*PFNGLVERTEXATTRIB2DARBPROC)(GLuint,GLdouble,GLdouble);
#endif
#if !defined(PFNGLVERTEXATTRIB2DPROC)
typedef void(*PFNGLVERTEXATTRIB2DPROC)(GLuint,GLdouble,GLdouble);
#endif
#if !defined(PFNGLVERTEXATTRIB2DNVPROC)
typedef void(*PFNGLVERTEXATTRIB2DNVPROC)(GLuint,GLdouble,GLdouble);
#endif
#if !defined(PFNGLVERTEXATTRIB2DVARBPROC)
typedef void(*PFNGLVERTEXATTRIB2DVARBPROC)(GLuint,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIB2DVPROC)
typedef void(*PFNGLVERTEXATTRIB2DVPROC)(GLuint,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIB2DVNVPROC)
typedef void(*PFNGLVERTEXATTRIB2DVNVPROC)(GLuint,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIB2FARBPROC)
typedef void(*PFNGLVERTEXATTRIB2FARBPROC)(GLuint,GLfloat,GLfloat);
#endif
#if !defined(PFNGLVERTEXATTRIB2FPROC)
typedef void(*PFNGLVERTEXATTRIB2FPROC)(GLuint,GLfloat,GLfloat);
#endif
#if !defined(PFNGLVERTEXATTRIB2FNVPROC)
typedef void(*PFNGLVERTEXATTRIB2FNVPROC)(GLuint,GLfloat,GLfloat);
#endif
#if !defined(PFNGLVERTEXATTRIB2FVARBPROC)
typedef void(*PFNGLVERTEXATTRIB2FVARBPROC)(GLuint,const GLfloat*);
#endif
#if !defined(PFNGLVERTEXATTRIB2FVPROC)
typedef void(*PFNGLVERTEXATTRIB2FVPROC)(GLuint,const GLfloat*);
#endif
#if !defined(PFNGLVERTEXATTRIB2FVNVPROC)
typedef void(*PFNGLVERTEXATTRIB2FVNVPROC)(GLuint,const GLfloat*);
#endif
#if !defined(PFNGLVERTEXATTRIB2HNVPROC)
typedef void(*PFNGLVERTEXATTRIB2HNVPROC)(GLuint,GLhalfNV,GLhalfNV);
#endif
#if !defined(PFNGLVERTEXATTRIB2HVNVPROC)
typedef void(*PFNGLVERTEXATTRIB2HVNVPROC)(GLuint,const GLhalfNV*);
#endif
#if !defined(PFNGLVERTEXATTRIB2SARBPROC)
typedef void(*PFNGLVERTEXATTRIB2SARBPROC)(GLuint,GLshort,GLshort);
#endif
#if !defined(PFNGLVERTEXATTRIB2SPROC)
typedef void(*PFNGLVERTEXATTRIB2SPROC)(GLuint,GLshort,GLshort);
#endif
#if !defined(PFNGLVERTEXATTRIB2SNVPROC)
typedef void(*PFNGLVERTEXATTRIB2SNVPROC)(GLuint,GLshort,GLshort);
#endif
#if !defined(PFNGLVERTEXATTRIB2SVARBPROC)
typedef void(*PFNGLVERTEXATTRIB2SVARBPROC)(GLuint,const GLshort*);
#endif
#if !defined(PFNGLVERTEXATTRIB2SVPROC)
typedef void(*PFNGLVERTEXATTRIB2SVPROC)(GLuint,const GLshort*);
#endif
#if !defined(PFNGLVERTEXATTRIB2SVNVPROC)
typedef void(*PFNGLVERTEXATTRIB2SVNVPROC)(GLuint,const GLshort*);
#endif
#if !defined(PFNGLVERTEXATTRIB3DARBPROC)
typedef void(*PFNGLVERTEXATTRIB3DARBPROC)(GLuint,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLVERTEXATTRIB3DPROC)
typedef void(*PFNGLVERTEXATTRIB3DPROC)(GLuint,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLVERTEXATTRIB3DNVPROC)
typedef void(*PFNGLVERTEXATTRIB3DNVPROC)(GLuint,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLVERTEXATTRIB3DVARBPROC)
typedef void(*PFNGLVERTEXATTRIB3DVARBPROC)(GLuint,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIB3DVPROC)
typedef void(*PFNGLVERTEXATTRIB3DVPROC)(GLuint,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIB3DVNVPROC)
typedef void(*PFNGLVERTEXATTRIB3DVNVPROC)(GLuint,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIB3FARBPROC)
typedef void(*PFNGLVERTEXATTRIB3FARBPROC)(GLuint,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLVERTEXATTRIB3FPROC)
typedef void(*PFNGLVERTEXATTRIB3FPROC)(GLuint,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLVERTEXATTRIB3FNVPROC)
typedef void(*PFNGLVERTEXATTRIB3FNVPROC)(GLuint,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLVERTEXATTRIB3FVARBPROC)
typedef void(*PFNGLVERTEXATTRIB3FVARBPROC)(GLuint,const GLfloat*);
#endif
#if !defined(PFNGLVERTEXATTRIB3FVPROC)
typedef void(*PFNGLVERTEXATTRIB3FVPROC)(GLuint,const GLfloat*);
#endif
#if !defined(PFNGLVERTEXATTRIB3FVNVPROC)
typedef void(*PFNGLVERTEXATTRIB3FVNVPROC)(GLuint,const GLfloat*);
#endif
#if !defined(PFNGLVERTEXATTRIB3HNVPROC)
typedef void(*PFNGLVERTEXATTRIB3HNVPROC)(GLuint,GLhalfNV,GLhalfNV,GLhalfNV);
#endif
#if !defined(PFNGLVERTEXATTRIB3HVNVPROC)
typedef void(*PFNGLVERTEXATTRIB3HVNVPROC)(GLuint,const GLhalfNV*);
#endif
#if !defined(PFNGLVERTEXATTRIB3SARBPROC)
typedef void(*PFNGLVERTEXATTRIB3SARBPROC)(GLuint,GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLVERTEXATTRIB3SPROC)
typedef void(*PFNGLVERTEXATTRIB3SPROC)(GLuint,GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLVERTEXATTRIB3SNVPROC)
typedef void(*PFNGLVERTEXATTRIB3SNVPROC)(GLuint,GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLVERTEXATTRIB3SVARBPROC)
typedef void(*PFNGLVERTEXATTRIB3SVARBPROC)(GLuint,const GLshort*);
#endif
#if !defined(PFNGLVERTEXATTRIB3SVPROC)
typedef void(*PFNGLVERTEXATTRIB3SVPROC)(GLuint,const GLshort*);
#endif
#if !defined(PFNGLVERTEXATTRIB3SVNVPROC)
typedef void(*PFNGLVERTEXATTRIB3SVNVPROC)(GLuint,const GLshort*);
#endif
#if !defined(PFNGLVERTEXATTRIB4BVARBPROC)
typedef void(*PFNGLVERTEXATTRIB4BVARBPROC)(GLuint,const GLbyte*);
#endif
#if !defined(PFNGLVERTEXATTRIB4BVPROC)
typedef void(*PFNGLVERTEXATTRIB4BVPROC)(GLuint,const GLbyte*);
#endif
#if !defined(PFNGLVERTEXATTRIB4DARBPROC)
typedef void(*PFNGLVERTEXATTRIB4DARBPROC)(GLuint,GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLVERTEXATTRIB4DPROC)
typedef void(*PFNGLVERTEXATTRIB4DPROC)(GLuint,GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLVERTEXATTRIB4DNVPROC)
typedef void(*PFNGLVERTEXATTRIB4DNVPROC)(GLuint,GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLVERTEXATTRIB4DVARBPROC)
typedef void(*PFNGLVERTEXATTRIB4DVARBPROC)(GLuint,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIB4DVPROC)
typedef void(*PFNGLVERTEXATTRIB4DVPROC)(GLuint,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIB4DVNVPROC)
typedef void(*PFNGLVERTEXATTRIB4DVNVPROC)(GLuint,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIB4FARBPROC)
typedef void(*PFNGLVERTEXATTRIB4FARBPROC)(GLuint,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLVERTEXATTRIB4FPROC)
typedef void(*PFNGLVERTEXATTRIB4FPROC)(GLuint,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLVERTEXATTRIB4FNVPROC)
typedef void(*PFNGLVERTEXATTRIB4FNVPROC)(GLuint,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLVERTEXATTRIB4FVARBPROC)
typedef void(*PFNGLVERTEXATTRIB4FVARBPROC)(GLuint,const GLfloat*);
#endif
#if !defined(PFNGLVERTEXATTRIB4FVPROC)
typedef void(*PFNGLVERTEXATTRIB4FVPROC)(GLuint,const GLfloat*);
#endif
#if !defined(PFNGLVERTEXATTRIB4FVNVPROC)
typedef void(*PFNGLVERTEXATTRIB4FVNVPROC)(GLuint,const GLfloat*);
#endif
#if !defined(PFNGLVERTEXATTRIB4HNVPROC)
typedef void(*PFNGLVERTEXATTRIB4HNVPROC)(GLuint,GLhalfNV,GLhalfNV,GLhalfNV,GLhalfNV);
#endif
#if !defined(PFNGLVERTEXATTRIB4HVNVPROC)
typedef void(*PFNGLVERTEXATTRIB4HVNVPROC)(GLuint,const GLhalfNV*);
#endif
#if !defined(PFNGLVERTEXATTRIB4IVARBPROC)
typedef void(*PFNGLVERTEXATTRIB4IVARBPROC)(GLuint,const GLint*);
#endif
#if !defined(PFNGLVERTEXATTRIB4IVPROC)
typedef void(*PFNGLVERTEXATTRIB4IVPROC)(GLuint,const GLint*);
#endif
#if !defined(PFNGLVERTEXATTRIB4NBVARBPROC)
typedef void(*PFNGLVERTEXATTRIB4NBVARBPROC)(GLuint,const GLbyte*);
#endif
#if !defined(PFNGLVERTEXATTRIB4NBVPROC)
typedef void(*PFNGLVERTEXATTRIB4NBVPROC)(GLuint,const GLbyte*);
#endif
#if !defined(PFNGLVERTEXATTRIB4NIVARBPROC)
typedef void(*PFNGLVERTEXATTRIB4NIVARBPROC)(GLuint,const GLint*);
#endif
#if !defined(PFNGLVERTEXATTRIB4NIVPROC)
typedef void(*PFNGLVERTEXATTRIB4NIVPROC)(GLuint,const GLint*);
#endif
#if !defined(PFNGLVERTEXATTRIB4NSVARBPROC)
typedef void(*PFNGLVERTEXATTRIB4NSVARBPROC)(GLuint,const GLshort*);
#endif
#if !defined(PFNGLVERTEXATTRIB4NSVPROC)
typedef void(*PFNGLVERTEXATTRIB4NSVPROC)(GLuint,const GLshort*);
#endif
#if !defined(PFNGLVERTEXATTRIB4NUBARBPROC)
typedef void(*PFNGLVERTEXATTRIB4NUBARBPROC)(GLuint,GLubyte,GLubyte,GLubyte,GLubyte);
#endif
#if !defined(PFNGLVERTEXATTRIB4NUBPROC)
typedef void(*PFNGLVERTEXATTRIB4NUBPROC)(GLuint,GLubyte,GLubyte,GLubyte,GLubyte);
#endif
#if !defined(PFNGLVERTEXATTRIB4NUBVARBPROC)
typedef void(*PFNGLVERTEXATTRIB4NUBVARBPROC)(GLuint,const GLubyte*);
#endif
#if !defined(PFNGLVERTEXATTRIB4NUBVPROC)
typedef void(*PFNGLVERTEXATTRIB4NUBVPROC)(GLuint,const GLubyte*);
#endif
#if !defined(PFNGLVERTEXATTRIB4NUIVARBPROC)
typedef void(*PFNGLVERTEXATTRIB4NUIVARBPROC)(GLuint,const GLuint*);
#endif
#if !defined(PFNGLVERTEXATTRIB4NUIVPROC)
typedef void(*PFNGLVERTEXATTRIB4NUIVPROC)(GLuint,const GLuint*);
#endif
#if !defined(PFNGLVERTEXATTRIB4NUSVARBPROC)
typedef void(*PFNGLVERTEXATTRIB4NUSVARBPROC)(GLuint,const GLushort*);
#endif
#if !defined(PFNGLVERTEXATTRIB4NUSVPROC)
typedef void(*PFNGLVERTEXATTRIB4NUSVPROC)(GLuint,const GLushort*);
#endif
#if !defined(PFNGLVERTEXATTRIB4SARBPROC)
typedef void(*PFNGLVERTEXATTRIB4SARBPROC)(GLuint,GLshort,GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLVERTEXATTRIB4SPROC)
typedef void(*PFNGLVERTEXATTRIB4SPROC)(GLuint,GLshort,GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLVERTEXATTRIB4SNVPROC)
typedef void(*PFNGLVERTEXATTRIB4SNVPROC)(GLuint,GLshort,GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLVERTEXATTRIB4SVARBPROC)
typedef void(*PFNGLVERTEXATTRIB4SVARBPROC)(GLuint,const GLshort*);
#endif
#if !defined(PFNGLVERTEXATTRIB4SVPROC)
typedef void(*PFNGLVERTEXATTRIB4SVPROC)(GLuint,const GLshort*);
#endif
#if !defined(PFNGLVERTEXATTRIB4SVNVPROC)
typedef void(*PFNGLVERTEXATTRIB4SVNVPROC)(GLuint,const GLshort*);
#endif
#if !defined(PFNGLVERTEXATTRIB4UBNVPROC)
typedef void(*PFNGLVERTEXATTRIB4UBNVPROC)(GLuint,GLubyte,GLubyte,GLubyte,GLubyte);
#endif
#if !defined(PFNGLVERTEXATTRIB4UBVARBPROC)
typedef void(*PFNGLVERTEXATTRIB4UBVARBPROC)(GLuint,const GLubyte*);
#endif
#if !defined(PFNGLVERTEXATTRIB4UBVPROC)
typedef void(*PFNGLVERTEXATTRIB4UBVPROC)(GLuint,const GLubyte*);
#endif
#if !defined(PFNGLVERTEXATTRIB4UBVNVPROC)
typedef void(*PFNGLVERTEXATTRIB4UBVNVPROC)(GLuint,const GLubyte*);
#endif
#if !defined(PFNGLVERTEXATTRIB4UIVARBPROC)
typedef void(*PFNGLVERTEXATTRIB4UIVARBPROC)(GLuint,const GLuint*);
#endif
#if !defined(PFNGLVERTEXATTRIB4UIVPROC)
typedef void(*PFNGLVERTEXATTRIB4UIVPROC)(GLuint,const GLuint*);
#endif
#if !defined(PFNGLVERTEXATTRIB4USVARBPROC)
typedef void(*PFNGLVERTEXATTRIB4USVARBPROC)(GLuint,const GLushort*);
#endif
#if !defined(PFNGLVERTEXATTRIB4USVPROC)
typedef void(*PFNGLVERTEXATTRIB4USVPROC)(GLuint,const GLushort*);
#endif
#if !defined(PFNGLVERTEXATTRIBARRAYOBJECTATIPROC)
typedef void(*PFNGLVERTEXATTRIBARRAYOBJECTATIPROC)(GLuint,GLint,GLenum,GLboolean,GLsizei,GLuint,GLuint);
#endif
#if !defined(PFNGLVERTEXATTRIBBINDINGPROC)
typedef void(*PFNGLVERTEXATTRIBBINDINGPROC)(GLuint,GLuint);
#endif
#if !defined(PFNGLVERTEXATTRIBDIVISORARBPROC)
typedef void(*PFNGLVERTEXATTRIBDIVISORARBPROC)(GLuint,GLuint);
#endif
#if !defined(PFNGLVERTEXATTRIBDIVISORPROC)
typedef void(*PFNGLVERTEXATTRIBDIVISORPROC)(GLuint,GLuint);
#endif
#if !defined(PFNGLVERTEXATTRIBFORMATPROC)
typedef void(*PFNGLVERTEXATTRIBFORMATPROC)(GLuint,GLint,GLenum,GLboolean,GLuint);
#endif
#if !defined(PFNGLVERTEXATTRIBFORMATNVPROC)
typedef void(*PFNGLVERTEXATTRIBFORMATNVPROC)(GLuint,GLint,GLenum,GLboolean,GLsizei);
#endif
#if !defined(PFNGLVERTEXATTRIBI1IEXTPROC)
typedef void(*PFNGLVERTEXATTRIBI1IEXTPROC)(GLuint,GLint);
#endif
#if !defined(PFNGLVERTEXATTRIBI1IPROC)
typedef void(*PFNGLVERTEXATTRIBI1IPROC)(GLuint,GLint);
#endif
#if !defined(PFNGLVERTEXATTRIBI1IVEXTPROC)
typedef void(*PFNGLVERTEXATTRIBI1IVEXTPROC)(GLuint,const GLint*);
#endif
#if !defined(PFNGLVERTEXATTRIBI1IVPROC)
typedef void(*PFNGLVERTEXATTRIBI1IVPROC)(GLuint,const GLint*);
#endif
#if !defined(PFNGLVERTEXATTRIBI1UIEXTPROC)
typedef void(*PFNGLVERTEXATTRIBI1UIEXTPROC)(GLuint,GLuint);
#endif
#if !defined(PFNGLVERTEXATTRIBI1UIPROC)
typedef void(*PFNGLVERTEXATTRIBI1UIPROC)(GLuint,GLuint);
#endif
#if !defined(PFNGLVERTEXATTRIBI1UIVEXTPROC)
typedef void(*PFNGLVERTEXATTRIBI1UIVEXTPROC)(GLuint,const GLuint*);
#endif
#if !defined(PFNGLVERTEXATTRIBI1UIVPROC)
typedef void(*PFNGLVERTEXATTRIBI1UIVPROC)(GLuint,const GLuint*);
#endif
#if !defined(PFNGLVERTEXATTRIBI2IEXTPROC)
typedef void(*PFNGLVERTEXATTRIBI2IEXTPROC)(GLuint,GLint,GLint);
#endif
#if !defined(PFNGLVERTEXATTRIBI2IPROC)
typedef void(*PFNGLVERTEXATTRIBI2IPROC)(GLuint,GLint,GLint);
#endif
#if !defined(PFNGLVERTEXATTRIBI2IVEXTPROC)
typedef void(*PFNGLVERTEXATTRIBI2IVEXTPROC)(GLuint,const GLint*);
#endif
#if !defined(PFNGLVERTEXATTRIBI2IVPROC)
typedef void(*PFNGLVERTEXATTRIBI2IVPROC)(GLuint,const GLint*);
#endif
#if !defined(PFNGLVERTEXATTRIBI2UIEXTPROC)
typedef void(*PFNGLVERTEXATTRIBI2UIEXTPROC)(GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLVERTEXATTRIBI2UIPROC)
typedef void(*PFNGLVERTEXATTRIBI2UIPROC)(GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLVERTEXATTRIBI2UIVEXTPROC)
typedef void(*PFNGLVERTEXATTRIBI2UIVEXTPROC)(GLuint,const GLuint*);
#endif
#if !defined(PFNGLVERTEXATTRIBI2UIVPROC)
typedef void(*PFNGLVERTEXATTRIBI2UIVPROC)(GLuint,const GLuint*);
#endif
#if !defined(PFNGLVERTEXATTRIBI3IEXTPROC)
typedef void(*PFNGLVERTEXATTRIBI3IEXTPROC)(GLuint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLVERTEXATTRIBI3IPROC)
typedef void(*PFNGLVERTEXATTRIBI3IPROC)(GLuint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLVERTEXATTRIBI3IVEXTPROC)
typedef void(*PFNGLVERTEXATTRIBI3IVEXTPROC)(GLuint,const GLint*);
#endif
#if !defined(PFNGLVERTEXATTRIBI3IVPROC)
typedef void(*PFNGLVERTEXATTRIBI3IVPROC)(GLuint,const GLint*);
#endif
#if !defined(PFNGLVERTEXATTRIBI3UIEXTPROC)
typedef void(*PFNGLVERTEXATTRIBI3UIEXTPROC)(GLuint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLVERTEXATTRIBI3UIPROC)
typedef void(*PFNGLVERTEXATTRIBI3UIPROC)(GLuint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLVERTEXATTRIBI3UIVEXTPROC)
typedef void(*PFNGLVERTEXATTRIBI3UIVEXTPROC)(GLuint,const GLuint*);
#endif
#if !defined(PFNGLVERTEXATTRIBI3UIVPROC)
typedef void(*PFNGLVERTEXATTRIBI3UIVPROC)(GLuint,const GLuint*);
#endif
#if !defined(PFNGLVERTEXATTRIBI4BVEXTPROC)
typedef void(*PFNGLVERTEXATTRIBI4BVEXTPROC)(GLuint,const GLbyte*);
#endif
#if !defined(PFNGLVERTEXATTRIBI4BVPROC)
typedef void(*PFNGLVERTEXATTRIBI4BVPROC)(GLuint,const GLbyte*);
#endif
#if !defined(PFNGLVERTEXATTRIBI4IEXTPROC)
typedef void(*PFNGLVERTEXATTRIBI4IEXTPROC)(GLuint,GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLVERTEXATTRIBI4IPROC)
typedef void(*PFNGLVERTEXATTRIBI4IPROC)(GLuint,GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLVERTEXATTRIBI4IVEXTPROC)
typedef void(*PFNGLVERTEXATTRIBI4IVEXTPROC)(GLuint,const GLint*);
#endif
#if !defined(PFNGLVERTEXATTRIBI4IVPROC)
typedef void(*PFNGLVERTEXATTRIBI4IVPROC)(GLuint,const GLint*);
#endif
#if !defined(PFNGLVERTEXATTRIBI4SVEXTPROC)
typedef void(*PFNGLVERTEXATTRIBI4SVEXTPROC)(GLuint,const GLshort*);
#endif
#if !defined(PFNGLVERTEXATTRIBI4SVPROC)
typedef void(*PFNGLVERTEXATTRIBI4SVPROC)(GLuint,const GLshort*);
#endif
#if !defined(PFNGLVERTEXATTRIBI4UBVEXTPROC)
typedef void(*PFNGLVERTEXATTRIBI4UBVEXTPROC)(GLuint,const GLubyte*);
#endif
#if !defined(PFNGLVERTEXATTRIBI4UBVPROC)
typedef void(*PFNGLVERTEXATTRIBI4UBVPROC)(GLuint,const GLubyte*);
#endif
#if !defined(PFNGLVERTEXATTRIBI4UIEXTPROC)
typedef void(*PFNGLVERTEXATTRIBI4UIEXTPROC)(GLuint,GLuint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLVERTEXATTRIBI4UIPROC)
typedef void(*PFNGLVERTEXATTRIBI4UIPROC)(GLuint,GLuint,GLuint,GLuint,GLuint);
#endif
#if !defined(PFNGLVERTEXATTRIBI4UIVEXTPROC)
typedef void(*PFNGLVERTEXATTRIBI4UIVEXTPROC)(GLuint,const GLuint*);
#endif
#if !defined(PFNGLVERTEXATTRIBI4UIVPROC)
typedef void(*PFNGLVERTEXATTRIBI4UIVPROC)(GLuint,const GLuint*);
#endif
#if !defined(PFNGLVERTEXATTRIBI4USVEXTPROC)
typedef void(*PFNGLVERTEXATTRIBI4USVEXTPROC)(GLuint,const GLushort*);
#endif
#if !defined(PFNGLVERTEXATTRIBI4USVPROC)
typedef void(*PFNGLVERTEXATTRIBI4USVPROC)(GLuint,const GLushort*);
#endif
#if !defined(PFNGLVERTEXATTRIBIFORMATPROC)
typedef void(*PFNGLVERTEXATTRIBIFORMATPROC)(GLuint,GLint,GLenum,GLuint);
#endif
#if !defined(PFNGLVERTEXATTRIBIFORMATNVPROC)
typedef void(*PFNGLVERTEXATTRIBIFORMATNVPROC)(GLuint,GLint,GLenum,GLsizei);
#endif
#if !defined(PFNGLVERTEXATTRIBIPOINTEREXTPROC)
typedef void(*PFNGLVERTEXATTRIBIPOINTEREXTPROC)(GLuint,GLint,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLVERTEXATTRIBIPOINTERPROC)
typedef void(*PFNGLVERTEXATTRIBIPOINTERPROC)(GLuint,GLint,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLVERTEXATTRIBL1DEXTPROC)
typedef void(*PFNGLVERTEXATTRIBL1DEXTPROC)(GLuint,GLdouble);
#endif
#if !defined(PFNGLVERTEXATTRIBL1DPROC)
typedef void(*PFNGLVERTEXATTRIBL1DPROC)(GLuint,GLdouble);
#endif
#if !defined(PFNGLVERTEXATTRIBL1DVEXTPROC)
typedef void(*PFNGLVERTEXATTRIBL1DVEXTPROC)(GLuint,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIBL1DVPROC)
typedef void(*PFNGLVERTEXATTRIBL1DVPROC)(GLuint,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIBL1I64NVPROC)
typedef void(*PFNGLVERTEXATTRIBL1I64NVPROC)(GLuint,GLint64EXT);
#endif
#if !defined(PFNGLVERTEXATTRIBL1I64VNVPROC)
typedef void(*PFNGLVERTEXATTRIBL1I64VNVPROC)(GLuint,const GLint64EXT*);
#endif
#if !defined(PFNGLVERTEXATTRIBL1UI64ARBPROC)
typedef void(*PFNGLVERTEXATTRIBL1UI64ARBPROC)(GLuint,GLuint64EXT);
#endif
#if !defined(PFNGLVERTEXATTRIBL1UI64NVPROC)
typedef void(*PFNGLVERTEXATTRIBL1UI64NVPROC)(GLuint,GLuint64EXT);
#endif
#if !defined(PFNGLVERTEXATTRIBL1UI64VARBPROC)
typedef void(*PFNGLVERTEXATTRIBL1UI64VARBPROC)(GLuint,const GLuint64EXT*);
#endif
#if !defined(PFNGLVERTEXATTRIBL1UI64VNVPROC)
typedef void(*PFNGLVERTEXATTRIBL1UI64VNVPROC)(GLuint,const GLuint64EXT*);
#endif
#if !defined(PFNGLVERTEXATTRIBL2DEXTPROC)
typedef void(*PFNGLVERTEXATTRIBL2DEXTPROC)(GLuint,GLdouble,GLdouble);
#endif
#if !defined(PFNGLVERTEXATTRIBL2DPROC)
typedef void(*PFNGLVERTEXATTRIBL2DPROC)(GLuint,GLdouble,GLdouble);
#endif
#if !defined(PFNGLVERTEXATTRIBL2DVEXTPROC)
typedef void(*PFNGLVERTEXATTRIBL2DVEXTPROC)(GLuint,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIBL2DVPROC)
typedef void(*PFNGLVERTEXATTRIBL2DVPROC)(GLuint,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIBL2I64NVPROC)
typedef void(*PFNGLVERTEXATTRIBL2I64NVPROC)(GLuint,GLint64EXT,GLint64EXT);
#endif
#if !defined(PFNGLVERTEXATTRIBL2I64VNVPROC)
typedef void(*PFNGLVERTEXATTRIBL2I64VNVPROC)(GLuint,const GLint64EXT*);
#endif
#if !defined(PFNGLVERTEXATTRIBL2UI64NVPROC)
typedef void(*PFNGLVERTEXATTRIBL2UI64NVPROC)(GLuint,GLuint64EXT,GLuint64EXT);
#endif
#if !defined(PFNGLVERTEXATTRIBL2UI64VNVPROC)
typedef void(*PFNGLVERTEXATTRIBL2UI64VNVPROC)(GLuint,const GLuint64EXT*);
#endif
#if !defined(PFNGLVERTEXATTRIBL3DEXTPROC)
typedef void(*PFNGLVERTEXATTRIBL3DEXTPROC)(GLuint,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLVERTEXATTRIBL3DPROC)
typedef void(*PFNGLVERTEXATTRIBL3DPROC)(GLuint,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLVERTEXATTRIBL3DVEXTPROC)
typedef void(*PFNGLVERTEXATTRIBL3DVEXTPROC)(GLuint,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIBL3DVPROC)
typedef void(*PFNGLVERTEXATTRIBL3DVPROC)(GLuint,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIBL3I64NVPROC)
typedef void(*PFNGLVERTEXATTRIBL3I64NVPROC)(GLuint,GLint64EXT,GLint64EXT,GLint64EXT);
#endif
#if !defined(PFNGLVERTEXATTRIBL3I64VNVPROC)
typedef void(*PFNGLVERTEXATTRIBL3I64VNVPROC)(GLuint,const GLint64EXT*);
#endif
#if !defined(PFNGLVERTEXATTRIBL3UI64NVPROC)
typedef void(*PFNGLVERTEXATTRIBL3UI64NVPROC)(GLuint,GLuint64EXT,GLuint64EXT,GLuint64EXT);
#endif
#if !defined(PFNGLVERTEXATTRIBL3UI64VNVPROC)
typedef void(*PFNGLVERTEXATTRIBL3UI64VNVPROC)(GLuint,const GLuint64EXT*);
#endif
#if !defined(PFNGLVERTEXATTRIBL4DEXTPROC)
typedef void(*PFNGLVERTEXATTRIBL4DEXTPROC)(GLuint,GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLVERTEXATTRIBL4DPROC)
typedef void(*PFNGLVERTEXATTRIBL4DPROC)(GLuint,GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLVERTEXATTRIBL4DVEXTPROC)
typedef void(*PFNGLVERTEXATTRIBL4DVEXTPROC)(GLuint,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIBL4DVPROC)
typedef void(*PFNGLVERTEXATTRIBL4DVPROC)(GLuint,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIBL4I64NVPROC)
typedef void(*PFNGLVERTEXATTRIBL4I64NVPROC)(GLuint,GLint64EXT,GLint64EXT,GLint64EXT,GLint64EXT);
#endif
#if !defined(PFNGLVERTEXATTRIBL4I64VNVPROC)
typedef void(*PFNGLVERTEXATTRIBL4I64VNVPROC)(GLuint,const GLint64EXT*);
#endif
#if !defined(PFNGLVERTEXATTRIBL4UI64NVPROC)
typedef void(*PFNGLVERTEXATTRIBL4UI64NVPROC)(GLuint,GLuint64EXT,GLuint64EXT,GLuint64EXT,GLuint64EXT);
#endif
#if !defined(PFNGLVERTEXATTRIBL4UI64VNVPROC)
typedef void(*PFNGLVERTEXATTRIBL4UI64VNVPROC)(GLuint,const GLuint64EXT*);
#endif
#if !defined(PFNGLVERTEXATTRIBLFORMATPROC)
typedef void(*PFNGLVERTEXATTRIBLFORMATPROC)(GLuint,GLint,GLenum,GLuint);
#endif
#if !defined(PFNGLVERTEXATTRIBLFORMATNVPROC)
typedef void(*PFNGLVERTEXATTRIBLFORMATNVPROC)(GLuint,GLint,GLenum,GLsizei);
#endif
#if !defined(PFNGLVERTEXATTRIBLPOINTEREXTPROC)
typedef void(*PFNGLVERTEXATTRIBLPOINTEREXTPROC)(GLuint,GLint,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLVERTEXATTRIBLPOINTERPROC)
typedef void(*PFNGLVERTEXATTRIBLPOINTERPROC)(GLuint,GLint,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLVERTEXATTRIBP1UIPROC)
typedef void(*PFNGLVERTEXATTRIBP1UIPROC)(GLuint,GLenum,GLboolean,GLuint);
#endif
#if !defined(PFNGLVERTEXATTRIBP1UIVPROC)
typedef void(*PFNGLVERTEXATTRIBP1UIVPROC)(GLuint,GLenum,GLboolean,const GLuint*);
#endif
#if !defined(PFNGLVERTEXATTRIBP2UIPROC)
typedef void(*PFNGLVERTEXATTRIBP2UIPROC)(GLuint,GLenum,GLboolean,GLuint);
#endif
#if !defined(PFNGLVERTEXATTRIBP2UIVPROC)
typedef void(*PFNGLVERTEXATTRIBP2UIVPROC)(GLuint,GLenum,GLboolean,const GLuint*);
#endif
#if !defined(PFNGLVERTEXATTRIBP3UIPROC)
typedef void(*PFNGLVERTEXATTRIBP3UIPROC)(GLuint,GLenum,GLboolean,GLuint);
#endif
#if !defined(PFNGLVERTEXATTRIBP3UIVPROC)
typedef void(*PFNGLVERTEXATTRIBP3UIVPROC)(GLuint,GLenum,GLboolean,const GLuint*);
#endif
#if !defined(PFNGLVERTEXATTRIBP4UIPROC)
typedef void(*PFNGLVERTEXATTRIBP4UIPROC)(GLuint,GLenum,GLboolean,GLuint);
#endif
#if !defined(PFNGLVERTEXATTRIBP4UIVPROC)
typedef void(*PFNGLVERTEXATTRIBP4UIVPROC)(GLuint,GLenum,GLboolean,const GLuint*);
#endif
#if !defined(PFNGLVERTEXATTRIBPARAMETERIAMDPROC)
typedef void(*PFNGLVERTEXATTRIBPARAMETERIAMDPROC)(GLuint,GLenum,GLint);
#endif
#if !defined(PFNGLVERTEXATTRIBPOINTERARBPROC)
typedef void(*PFNGLVERTEXATTRIBPOINTERARBPROC)(GLuint,GLint,GLenum,GLboolean,GLsizei,const void*);
#endif
#if !defined(PFNGLVERTEXATTRIBPOINTERPROC)
typedef void(*PFNGLVERTEXATTRIBPOINTERPROC)(GLuint,GLint,GLenum,GLboolean,GLsizei,const void*);
#endif
#if !defined(PFNGLVERTEXATTRIBPOINTERNVPROC)
typedef void(*PFNGLVERTEXATTRIBPOINTERNVPROC)(GLuint,GLint,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLVERTEXATTRIBS1DVNVPROC)
typedef void(*PFNGLVERTEXATTRIBS1DVNVPROC)(GLuint,GLsizei,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIBS1FVNVPROC)
typedef void(*PFNGLVERTEXATTRIBS1FVNVPROC)(GLuint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLVERTEXATTRIBS1HVNVPROC)
typedef void(*PFNGLVERTEXATTRIBS1HVNVPROC)(GLuint,GLsizei,const GLhalfNV*);
#endif
#if !defined(PFNGLVERTEXATTRIBS1SVNVPROC)
typedef void(*PFNGLVERTEXATTRIBS1SVNVPROC)(GLuint,GLsizei,const GLshort*);
#endif
#if !defined(PFNGLVERTEXATTRIBS2DVNVPROC)
typedef void(*PFNGLVERTEXATTRIBS2DVNVPROC)(GLuint,GLsizei,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIBS2FVNVPROC)
typedef void(*PFNGLVERTEXATTRIBS2FVNVPROC)(GLuint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLVERTEXATTRIBS2HVNVPROC)
typedef void(*PFNGLVERTEXATTRIBS2HVNVPROC)(GLuint,GLsizei,const GLhalfNV*);
#endif
#if !defined(PFNGLVERTEXATTRIBS2SVNVPROC)
typedef void(*PFNGLVERTEXATTRIBS2SVNVPROC)(GLuint,GLsizei,const GLshort*);
#endif
#if !defined(PFNGLVERTEXATTRIBS3DVNVPROC)
typedef void(*PFNGLVERTEXATTRIBS3DVNVPROC)(GLuint,GLsizei,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIBS3FVNVPROC)
typedef void(*PFNGLVERTEXATTRIBS3FVNVPROC)(GLuint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLVERTEXATTRIBS3HVNVPROC)
typedef void(*PFNGLVERTEXATTRIBS3HVNVPROC)(GLuint,GLsizei,const GLhalfNV*);
#endif
#if !defined(PFNGLVERTEXATTRIBS3SVNVPROC)
typedef void(*PFNGLVERTEXATTRIBS3SVNVPROC)(GLuint,GLsizei,const GLshort*);
#endif
#if !defined(PFNGLVERTEXATTRIBS4DVNVPROC)
typedef void(*PFNGLVERTEXATTRIBS4DVNVPROC)(GLuint,GLsizei,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXATTRIBS4FVNVPROC)
typedef void(*PFNGLVERTEXATTRIBS4FVNVPROC)(GLuint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLVERTEXATTRIBS4HVNVPROC)
typedef void(*PFNGLVERTEXATTRIBS4HVNVPROC)(GLuint,GLsizei,const GLhalfNV*);
#endif
#if !defined(PFNGLVERTEXATTRIBS4SVNVPROC)
typedef void(*PFNGLVERTEXATTRIBS4SVNVPROC)(GLuint,GLsizei,const GLshort*);
#endif
#if !defined(PFNGLVERTEXATTRIBS4UBVNVPROC)
typedef void(*PFNGLVERTEXATTRIBS4UBVNVPROC)(GLuint,GLsizei,const GLubyte*);
#endif
#if !defined(PFNGLVERTEXBINDINGDIVISORPROC)
typedef void(*PFNGLVERTEXBINDINGDIVISORPROC)(GLuint,GLuint);
#endif
#if !defined(PFNGLVERTEXBLENDARBPROC)
typedef void(*PFNGLVERTEXBLENDARBPROC)(GLint);
#endif
#if !defined(PFNGLVERTEXBLENDENVFATIPROC)
typedef void(*PFNGLVERTEXBLENDENVFATIPROC)(GLenum,GLfloat);
#endif
#if !defined(PFNGLVERTEXBLENDENVIATIPROC)
typedef void(*PFNGLVERTEXBLENDENVIATIPROC)(GLenum,GLint);
#endif
#if !defined(PFNGLVERTEXFORMATNVPROC)
typedef void(*PFNGLVERTEXFORMATNVPROC)(GLint,GLenum,GLsizei);
#endif
#if !defined(PFNGLVERTEXP2UIPROC)
typedef void(*PFNGLVERTEXP2UIPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLVERTEXP2UIVPROC)
typedef void(*PFNGLVERTEXP2UIVPROC)(GLenum,const GLuint*);
#endif
#if !defined(PFNGLVERTEXP3UIPROC)
typedef void(*PFNGLVERTEXP3UIPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLVERTEXP3UIVPROC)
typedef void(*PFNGLVERTEXP3UIVPROC)(GLenum,const GLuint*);
#endif
#if !defined(PFNGLVERTEXP4UIPROC)
typedef void(*PFNGLVERTEXP4UIPROC)(GLenum,GLuint);
#endif
#if !defined(PFNGLVERTEXP4UIVPROC)
typedef void(*PFNGLVERTEXP4UIVPROC)(GLenum,const GLuint*);
#endif
#if !defined(PFNGLVERTEXPOINTEREXTPROC)
typedef void(*PFNGLVERTEXPOINTEREXTPROC)(GLint,GLenum,GLsizei,GLsizei,const void*);
#endif
#if !defined(PFNGLVERTEXPOINTERPROC)
typedef void(*PFNGLVERTEXPOINTERPROC)(GLint,GLenum,GLsizei,const GLvoid*);
#endif
#if !defined(PFNGLVERTEXPOINTERLISTIBMPROC)
typedef void(*PFNGLVERTEXPOINTERLISTIBMPROC)(GLint,GLenum,GLint,const void**,GLint);
#endif
#if !defined(PFNGLVERTEXPOINTERVINTELPROC)
typedef void(*PFNGLVERTEXPOINTERVINTELPROC)(GLint,GLenum,const void**);
#endif
#if !defined(PFNGLVERTEXSTREAM1DATIPROC)
typedef void(*PFNGLVERTEXSTREAM1DATIPROC)(GLenum,GLdouble);
#endif
#if !defined(PFNGLVERTEXSTREAM1DVATIPROC)
typedef void(*PFNGLVERTEXSTREAM1DVATIPROC)(GLenum,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXSTREAM1FATIPROC)
typedef void(*PFNGLVERTEXSTREAM1FATIPROC)(GLenum,GLfloat);
#endif
#if !defined(PFNGLVERTEXSTREAM1FVATIPROC)
typedef void(*PFNGLVERTEXSTREAM1FVATIPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLVERTEXSTREAM1IATIPROC)
typedef void(*PFNGLVERTEXSTREAM1IATIPROC)(GLenum,GLint);
#endif
#if !defined(PFNGLVERTEXSTREAM1IVATIPROC)
typedef void(*PFNGLVERTEXSTREAM1IVATIPROC)(GLenum,const GLint*);
#endif
#if !defined(PFNGLVERTEXSTREAM1SATIPROC)
typedef void(*PFNGLVERTEXSTREAM1SATIPROC)(GLenum,GLshort);
#endif
#if !defined(PFNGLVERTEXSTREAM1SVATIPROC)
typedef void(*PFNGLVERTEXSTREAM1SVATIPROC)(GLenum,const GLshort*);
#endif
#if !defined(PFNGLVERTEXSTREAM2DATIPROC)
typedef void(*PFNGLVERTEXSTREAM2DATIPROC)(GLenum,GLdouble,GLdouble);
#endif
#if !defined(PFNGLVERTEXSTREAM2DVATIPROC)
typedef void(*PFNGLVERTEXSTREAM2DVATIPROC)(GLenum,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXSTREAM2FATIPROC)
typedef void(*PFNGLVERTEXSTREAM2FATIPROC)(GLenum,GLfloat,GLfloat);
#endif
#if !defined(PFNGLVERTEXSTREAM2FVATIPROC)
typedef void(*PFNGLVERTEXSTREAM2FVATIPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLVERTEXSTREAM2IATIPROC)
typedef void(*PFNGLVERTEXSTREAM2IATIPROC)(GLenum,GLint,GLint);
#endif
#if !defined(PFNGLVERTEXSTREAM2IVATIPROC)
typedef void(*PFNGLVERTEXSTREAM2IVATIPROC)(GLenum,const GLint*);
#endif
#if !defined(PFNGLVERTEXSTREAM2SATIPROC)
typedef void(*PFNGLVERTEXSTREAM2SATIPROC)(GLenum,GLshort,GLshort);
#endif
#if !defined(PFNGLVERTEXSTREAM2SVATIPROC)
typedef void(*PFNGLVERTEXSTREAM2SVATIPROC)(GLenum,const GLshort*);
#endif
#if !defined(PFNGLVERTEXSTREAM3DATIPROC)
typedef void(*PFNGLVERTEXSTREAM3DATIPROC)(GLenum,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLVERTEXSTREAM3DVATIPROC)
typedef void(*PFNGLVERTEXSTREAM3DVATIPROC)(GLenum,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXSTREAM3FATIPROC)
typedef void(*PFNGLVERTEXSTREAM3FATIPROC)(GLenum,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLVERTEXSTREAM3FVATIPROC)
typedef void(*PFNGLVERTEXSTREAM3FVATIPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLVERTEXSTREAM3IATIPROC)
typedef void(*PFNGLVERTEXSTREAM3IATIPROC)(GLenum,GLint,GLint,GLint);
#endif
#if !defined(PFNGLVERTEXSTREAM3IVATIPROC)
typedef void(*PFNGLVERTEXSTREAM3IVATIPROC)(GLenum,const GLint*);
#endif
#if !defined(PFNGLVERTEXSTREAM3SATIPROC)
typedef void(*PFNGLVERTEXSTREAM3SATIPROC)(GLenum,GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLVERTEXSTREAM3SVATIPROC)
typedef void(*PFNGLVERTEXSTREAM3SVATIPROC)(GLenum,const GLshort*);
#endif
#if !defined(PFNGLVERTEXSTREAM4DATIPROC)
typedef void(*PFNGLVERTEXSTREAM4DATIPROC)(GLenum,GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLVERTEXSTREAM4DVATIPROC)
typedef void(*PFNGLVERTEXSTREAM4DVATIPROC)(GLenum,const GLdouble*);
#endif
#if !defined(PFNGLVERTEXSTREAM4FATIPROC)
typedef void(*PFNGLVERTEXSTREAM4FATIPROC)(GLenum,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLVERTEXSTREAM4FVATIPROC)
typedef void(*PFNGLVERTEXSTREAM4FVATIPROC)(GLenum,const GLfloat*);
#endif
#if !defined(PFNGLVERTEXSTREAM4IATIPROC)
typedef void(*PFNGLVERTEXSTREAM4IATIPROC)(GLenum,GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLVERTEXSTREAM4IVATIPROC)
typedef void(*PFNGLVERTEXSTREAM4IVATIPROC)(GLenum,const GLint*);
#endif
#if !defined(PFNGLVERTEXSTREAM4SATIPROC)
typedef void(*PFNGLVERTEXSTREAM4SATIPROC)(GLenum,GLshort,GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLVERTEXSTREAM4SVATIPROC)
typedef void(*PFNGLVERTEXSTREAM4SVATIPROC)(GLenum,const GLshort*);
#endif
#if !defined(PFNGLVERTEXWEIGHTFEXTPROC)
typedef void(*PFNGLVERTEXWEIGHTFEXTPROC)(GLfloat);
#endif
#if !defined(PFNGLVERTEXWEIGHTFVEXTPROC)
typedef void(*PFNGLVERTEXWEIGHTFVEXTPROC)(const GLfloat*);
#endif
#if !defined(PFNGLVERTEXWEIGHTHNVPROC)
typedef void(*PFNGLVERTEXWEIGHTHNVPROC)(GLhalfNV);
#endif
#if !defined(PFNGLVERTEXWEIGHTHVNVPROC)
typedef void(*PFNGLVERTEXWEIGHTHVNVPROC)(const GLhalfNV*);
#endif
#if !defined(PFNGLVERTEXWEIGHTPOINTEREXTPROC)
typedef void(*PFNGLVERTEXWEIGHTPOINTEREXTPROC)(GLint,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLVIDEOCAPTURESTREAMPARAMETERDVNVPROC)
typedef void(*PFNGLVIDEOCAPTURESTREAMPARAMETERDVNVPROC)(GLuint,GLuint,GLenum,const GLdouble*);
#endif
#if !defined(PFNGLVIDEOCAPTURESTREAMPARAMETERFVNVPROC)
typedef void(*PFNGLVIDEOCAPTURESTREAMPARAMETERFVNVPROC)(GLuint,GLuint,GLenum,const GLfloat*);
#endif
#if !defined(PFNGLVIDEOCAPTURESTREAMPARAMETERIVNVPROC)
typedef void(*PFNGLVIDEOCAPTURESTREAMPARAMETERIVNVPROC)(GLuint,GLuint,GLenum,const GLint*);
#endif
#if !defined(PFNGLVIEWPORTARRAYVPROC)
typedef void(*PFNGLVIEWPORTARRAYVPROC)(GLuint,GLsizei,const GLfloat*);
#endif
#if !defined(PFNGLVIEWPORTPROC)
typedef void(*PFNGLVIEWPORTPROC)(GLint,GLint,GLsizei,GLsizei);
#endif
#if !defined(PFNGLVIEWPORTINDEXEDFPROC)
typedef void(*PFNGLVIEWPORTINDEXEDFPROC)(GLuint,GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLVIEWPORTINDEXEDFVPROC)
typedef void(*PFNGLVIEWPORTINDEXEDFVPROC)(GLuint,const GLfloat*);
#endif
#if !defined(PFNGLVIEWPORTSWIZZLENVPROC)
typedef void(*PFNGLVIEWPORTSWIZZLENVPROC)(GLuint,GLenum,GLenum,GLenum,GLenum);
#endif
#if !defined(PFNGLWAITSYNCPROC)
typedef void(*PFNGLWAITSYNCPROC)(GLsync,GLbitfield,GLuint64);
#endif
#if !defined(PFNGLWEIGHTBVARBPROC)
typedef void(*PFNGLWEIGHTBVARBPROC)(GLint,const GLbyte*);
#endif
#if !defined(PFNGLWEIGHTDVARBPROC)
typedef void(*PFNGLWEIGHTDVARBPROC)(GLint,const GLdouble*);
#endif
#if !defined(PFNGLWEIGHTFVARBPROC)
typedef void(*PFNGLWEIGHTFVARBPROC)(GLint,const GLfloat*);
#endif
#if !defined(PFNGLWEIGHTIVARBPROC)
typedef void(*PFNGLWEIGHTIVARBPROC)(GLint,const GLint*);
#endif
#if !defined(PFNGLWEIGHTPATHSNVPROC)
typedef void(*PFNGLWEIGHTPATHSNVPROC)(GLuint,GLsizei,const GLuint*,const GLfloat*);
#endif
#if !defined(PFNGLWEIGHTPOINTERARBPROC)
typedef void(*PFNGLWEIGHTPOINTERARBPROC)(GLint,GLenum,GLsizei,const void*);
#endif
#if !defined(PFNGLWEIGHTSVARBPROC)
typedef void(*PFNGLWEIGHTSVARBPROC)(GLint,const GLshort*);
#endif
#if !defined(PFNGLWEIGHTUBVARBPROC)
typedef void(*PFNGLWEIGHTUBVARBPROC)(GLint,const GLubyte*);
#endif
#if !defined(PFNGLWEIGHTUIVARBPROC)
typedef void(*PFNGLWEIGHTUIVARBPROC)(GLint,const GLuint*);
#endif
#if !defined(PFNGLWEIGHTUSVARBPROC)
typedef void(*PFNGLWEIGHTUSVARBPROC)(GLint,const GLushort*);
#endif
#if !defined(PFNGLWINDOWPOS2DARBPROC)
typedef void(*PFNGLWINDOWPOS2DARBPROC)(GLdouble,GLdouble);
#endif
#if !defined(PFNGLWINDOWPOS2DPROC)
typedef void(*PFNGLWINDOWPOS2DPROC)(GLdouble,GLdouble);
#endif
#if !defined(PFNGLWINDOWPOS2DMESAPROC)
typedef void(*PFNGLWINDOWPOS2DMESAPROC)(GLdouble,GLdouble);
#endif
#if !defined(PFNGLWINDOWPOS2DVARBPROC)
typedef void(*PFNGLWINDOWPOS2DVARBPROC)(const GLdouble*);
#endif
#if !defined(PFNGLWINDOWPOS2DVPROC)
typedef void(*PFNGLWINDOWPOS2DVPROC)(const GLdouble*);
#endif
#if !defined(PFNGLWINDOWPOS2DVMESAPROC)
typedef void(*PFNGLWINDOWPOS2DVMESAPROC)(const GLdouble*);
#endif
#if !defined(PFNGLWINDOWPOS2FARBPROC)
typedef void(*PFNGLWINDOWPOS2FARBPROC)(GLfloat,GLfloat);
#endif
#if !defined(PFNGLWINDOWPOS2FPROC)
typedef void(*PFNGLWINDOWPOS2FPROC)(GLfloat,GLfloat);
#endif
#if !defined(PFNGLWINDOWPOS2FMESAPROC)
typedef void(*PFNGLWINDOWPOS2FMESAPROC)(GLfloat,GLfloat);
#endif
#if !defined(PFNGLWINDOWPOS2FVARBPROC)
typedef void(*PFNGLWINDOWPOS2FVARBPROC)(const GLfloat*);
#endif
#if !defined(PFNGLWINDOWPOS2FVPROC)
typedef void(*PFNGLWINDOWPOS2FVPROC)(const GLfloat*);
#endif
#if !defined(PFNGLWINDOWPOS2FVMESAPROC)
typedef void(*PFNGLWINDOWPOS2FVMESAPROC)(const GLfloat*);
#endif
#if !defined(PFNGLWINDOWPOS2IARBPROC)
typedef void(*PFNGLWINDOWPOS2IARBPROC)(GLint,GLint);
#endif
#if !defined(PFNGLWINDOWPOS2IPROC)
typedef void(*PFNGLWINDOWPOS2IPROC)(GLint,GLint);
#endif
#if !defined(PFNGLWINDOWPOS2IMESAPROC)
typedef void(*PFNGLWINDOWPOS2IMESAPROC)(GLint,GLint);
#endif
#if !defined(PFNGLWINDOWPOS2IVARBPROC)
typedef void(*PFNGLWINDOWPOS2IVARBPROC)(const GLint*);
#endif
#if !defined(PFNGLWINDOWPOS2IVPROC)
typedef void(*PFNGLWINDOWPOS2IVPROC)(const GLint*);
#endif
#if !defined(PFNGLWINDOWPOS2IVMESAPROC)
typedef void(*PFNGLWINDOWPOS2IVMESAPROC)(const GLint*);
#endif
#if !defined(PFNGLWINDOWPOS2SARBPROC)
typedef void(*PFNGLWINDOWPOS2SARBPROC)(GLshort,GLshort);
#endif
#if !defined(PFNGLWINDOWPOS2SPROC)
typedef void(*PFNGLWINDOWPOS2SPROC)(GLshort,GLshort);
#endif
#if !defined(PFNGLWINDOWPOS2SMESAPROC)
typedef void(*PFNGLWINDOWPOS2SMESAPROC)(GLshort,GLshort);
#endif
#if !defined(PFNGLWINDOWPOS2SVARBPROC)
typedef void(*PFNGLWINDOWPOS2SVARBPROC)(const GLshort*);
#endif
#if !defined(PFNGLWINDOWPOS2SVPROC)
typedef void(*PFNGLWINDOWPOS2SVPROC)(const GLshort*);
#endif
#if !defined(PFNGLWINDOWPOS2SVMESAPROC)
typedef void(*PFNGLWINDOWPOS2SVMESAPROC)(const GLshort*);
#endif
#if !defined(PFNGLWINDOWPOS3DARBPROC)
typedef void(*PFNGLWINDOWPOS3DARBPROC)(GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLWINDOWPOS3DPROC)
typedef void(*PFNGLWINDOWPOS3DPROC)(GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLWINDOWPOS3DMESAPROC)
typedef void(*PFNGLWINDOWPOS3DMESAPROC)(GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLWINDOWPOS3DVARBPROC)
typedef void(*PFNGLWINDOWPOS3DVARBPROC)(const GLdouble*);
#endif
#if !defined(PFNGLWINDOWPOS3DVPROC)
typedef void(*PFNGLWINDOWPOS3DVPROC)(const GLdouble*);
#endif
#if !defined(PFNGLWINDOWPOS3DVMESAPROC)
typedef void(*PFNGLWINDOWPOS3DVMESAPROC)(const GLdouble*);
#endif
#if !defined(PFNGLWINDOWPOS3FARBPROC)
typedef void(*PFNGLWINDOWPOS3FARBPROC)(GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLWINDOWPOS3FPROC)
typedef void(*PFNGLWINDOWPOS3FPROC)(GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLWINDOWPOS3FMESAPROC)
typedef void(*PFNGLWINDOWPOS3FMESAPROC)(GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLWINDOWPOS3FVARBPROC)
typedef void(*PFNGLWINDOWPOS3FVARBPROC)(const GLfloat*);
#endif
#if !defined(PFNGLWINDOWPOS3FVPROC)
typedef void(*PFNGLWINDOWPOS3FVPROC)(const GLfloat*);
#endif
#if !defined(PFNGLWINDOWPOS3FVMESAPROC)
typedef void(*PFNGLWINDOWPOS3FVMESAPROC)(const GLfloat*);
#endif
#if !defined(PFNGLWINDOWPOS3IARBPROC)
typedef void(*PFNGLWINDOWPOS3IARBPROC)(GLint,GLint,GLint);
#endif
#if !defined(PFNGLWINDOWPOS3IPROC)
typedef void(*PFNGLWINDOWPOS3IPROC)(GLint,GLint,GLint);
#endif
#if !defined(PFNGLWINDOWPOS3IMESAPROC)
typedef void(*PFNGLWINDOWPOS3IMESAPROC)(GLint,GLint,GLint);
#endif
#if !defined(PFNGLWINDOWPOS3IVARBPROC)
typedef void(*PFNGLWINDOWPOS3IVARBPROC)(const GLint*);
#endif
#if !defined(PFNGLWINDOWPOS3IVPROC)
typedef void(*PFNGLWINDOWPOS3IVPROC)(const GLint*);
#endif
#if !defined(PFNGLWINDOWPOS3IVMESAPROC)
typedef void(*PFNGLWINDOWPOS3IVMESAPROC)(const GLint*);
#endif
#if !defined(PFNGLWINDOWPOS3SARBPROC)
typedef void(*PFNGLWINDOWPOS3SARBPROC)(GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLWINDOWPOS3SPROC)
typedef void(*PFNGLWINDOWPOS3SPROC)(GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLWINDOWPOS3SMESAPROC)
typedef void(*PFNGLWINDOWPOS3SMESAPROC)(GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLWINDOWPOS3SVARBPROC)
typedef void(*PFNGLWINDOWPOS3SVARBPROC)(const GLshort*);
#endif
#if !defined(PFNGLWINDOWPOS3SVPROC)
typedef void(*PFNGLWINDOWPOS3SVPROC)(const GLshort*);
#endif
#if !defined(PFNGLWINDOWPOS3SVMESAPROC)
typedef void(*PFNGLWINDOWPOS3SVMESAPROC)(const GLshort*);
#endif
#if !defined(PFNGLWINDOWPOS4DMESAPROC)
typedef void(*PFNGLWINDOWPOS4DMESAPROC)(GLdouble,GLdouble,GLdouble,GLdouble);
#endif
#if !defined(PFNGLWINDOWPOS4DVMESAPROC)
typedef void(*PFNGLWINDOWPOS4DVMESAPROC)(const GLdouble*);
#endif
#if !defined(PFNGLWINDOWPOS4FMESAPROC)
typedef void(*PFNGLWINDOWPOS4FMESAPROC)(GLfloat,GLfloat,GLfloat,GLfloat);
#endif
#if !defined(PFNGLWINDOWPOS4FVMESAPROC)
typedef void(*PFNGLWINDOWPOS4FVMESAPROC)(const GLfloat*);
#endif
#if !defined(PFNGLWINDOWPOS4IMESAPROC)
typedef void(*PFNGLWINDOWPOS4IMESAPROC)(GLint,GLint,GLint,GLint);
#endif
#if !defined(PFNGLWINDOWPOS4IVMESAPROC)
typedef void(*PFNGLWINDOWPOS4IVMESAPROC)(const GLint*);
#endif
#if !defined(PFNGLWINDOWPOS4SMESAPROC)
typedef void(*PFNGLWINDOWPOS4SMESAPROC)(GLshort,GLshort,GLshort,GLshort);
#endif
#if !defined(PFNGLWINDOWPOS4SVMESAPROC)
typedef void(*PFNGLWINDOWPOS4SVMESAPROC)(const GLshort*);
#endif
#if !defined(PFNGLWRITEMASKEXTPROC)
typedef void(*PFNGLWRITEMASKEXTPROC)(GLuint,GLuint,GLenum,GLenum,GLenum,GLenum);
#endif
