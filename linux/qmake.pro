INCLUDEPATH += /usr/include
INCLUDEPATH += /usr/local/include/SDL2
INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/include/freetype2
INCLUDEPATH += /usr/include/theoraplayer

QMAKE_LIBDIR += /usr/local/lib

LIBS += -lbass
LIBS += -lbass_fx
LIBS += -lfreeimage
LIBS += -ltheoraplayer
LIBS += -lz
LIBS += -lSDL2
LIBS += -lfreetype

TARGET = wmelite

HEADERS += ../src/SysClass.h
HEADERS += ../src/AdLayer.h
HEADERS += ../src/BSurface.h
HEADERS += ../src/SXFile.h
HEADERS += ../src/AdNodeState.h
HEADERS += ../src/PathUtil.h
HEADERS += ../src/AdActor.h
HEADERS += ../src/VidTheoraPlayer.h
HEADERS += ../src/AdPath.h
HEADERS += ../src/SysInstance.h
HEADERS += ../src/BBase.h
HEADERS += ../src/ScEngine.h
HEADERS += ../src/AdRegion.h
HEADERS += ../src/AdResponse.h
HEADERS += ../src/BPersistMgr.h
HEADERS += ../src/dcgf.h
HEADERS += ../src/SXMemBuffer.h
HEADERS += ../src/BDiskFile.h
HEADERS += ../src/BSurfaceSDL.h
HEADERS += ../src/SysClassRegistry.h
HEADERS += ../src/AdInventory.h
HEADERS += ../src/BRegistry.h
HEADERS += ../src/BSoundMgr.h
HEADERS += ../src/BStringTable.h
HEADERS += ../src/BRenderer.h
HEADERS += ../src/ScValue.h
HEADERS += ../src/AdActorDir.h
HEADERS += ../src/utils.h
HEADERS += ../src/IOS_StoreKit_interface.h
HEADERS += ../src/BFontStorage.h
HEADERS += ../src/BDebugger.h
HEADERS += ../src/BFileEntry.h
HEADERS += ../src/AdInventoryBox.h
HEADERS += ../src/UIEdit.h
HEADERS += ../src/AdObject.h
HEADERS += ../src/PartEmitter.h
HEADERS += ../src/AdResponseBox.h
HEADERS += ../src/BSoundBuffer.h
HEADERS += ../src/BDynBuffer.h
HEADERS += ../src/BGame.h
HEADERS += ../src/wintypes.h
HEADERS += ../src/AdTypes.h
HEADERS += ../src/BParser.h
HEADERS += ../src/BFont.h
HEADERS += ../src/SxObject.h
HEADERS += ../src/IOS_StoreKit.h
HEADERS += ../src/AdEntity.h
HEADERS += ../src/BTransitionMgr.h
HEADERS += ../src/AdGame.h
HEADERS += ../src/ios_utils.h
HEADERS += ../src/BScriptable.h
HEADERS += ../src/AdSpriteSet.h
HEADERS += ../src/AdSceneState.h
HEADERS += ../src/MathUtil.h
HEADERS += ../src/dcscript.h
HEADERS += ../src/PartForce.h
HEADERS += ../src/UIText.h
HEADERS += ../src/BKeyboardState.h
HEADERS += ../src/BFileManager.h
HEADERS += ../src/StringUtil.h
HEADERS += ../src/AdSentence.h
HEADERS += ../src/PlatformSDL.h
HEADERS += ../src/VidDataSource.h
HEADERS += ../src/dcpackage.h
HEADERS += ../src/SXDate.h
HEADERS += ../src/android/android.h
HEADERS += ../src/BEvent.h
HEADERS += ../src/UITiledImage.h
HEADERS += ../src/BScriptHolder.h
HEADERS += ../src/AdScaleLevel.h
HEADERS += ../src/BQuickMsg.h
HEADERS += ../src/SdlUtil.h
HEADERS += ../src/BRegion.h
HEADERS += ../src/AdWaypointGroup.h
HEADERS += ../src/VidManager.h
HEADERS += ../src/tinyxml.h
HEADERS += ../src/AdResponseContext.h
HEADERS += ../src/crc.h
HEADERS += ../src/ScStack.h
HEADERS += ../src/wme_debugger.h
HEADERS += ../src/BActiveRect.h
HEADERS += ../src/ScScript.h
HEADERS += ../src/DirectoryOperations.h
HEADERS += ../src/Vector2.h
HEADERS += ../src/AdRotLevel.h
HEADERS += ../src/BNamedObject.h
HEADERS += ../src/UIEntity.h
HEADERS += ../src/BPackage.h
HEADERS += ../src/SXStore.h
HEADERS += ../src/FontGlyphCache.h
HEADERS += ../src/BSaveThumbHelper.h
HEADERS += ../src/UIButton.h
HEADERS += ../src/BObject.h
HEADERS += ../src/AdSceneNode.h
HEADERS += ../src/UIObject.h
HEADERS += ../src/PartParticle.h
HEADERS += ../src/BFader.h
HEADERS += ../src/BResources.h
HEADERS += ../src/BImage.h
HEADERS += ../src/BSaveThumbFile.h
HEADERS += ../src/BSprite.h
HEADERS += ../src/BPkgFile.h
HEADERS += ../src/BPoint.h
HEADERS += ../src/BSurfaceStorage.h
HEADERS += ../src/SXArray.h
HEADERS += ../src/BViewport.h
HEADERS += ../src/Matrix4.h
HEADERS += ../src/coll_templ.h
HEADERS += ../src/ConvertUTF.h
HEADERS += ../src/AdTalkDef.h
HEADERS += ../src/BSubFrame.h
HEADERS += ../src/SXMath.h
HEADERS += ../src/BFrame.h
HEADERS += ../src/BSound.h
HEADERS += ../src/UIWindow.h
HEADERS += ../src/AdTalkHolder.h
HEADERS += ../src/BFontTT.h
HEADERS += ../src/AdTalkNode.h
HEADERS += ../src/SXString.h
HEADERS += ../src/BFile.h
HEADERS += ../src/BResourceFile.h
HEADERS += ../src/dctypes.h
HEADERS += ../src/FileOperations.h
HEADERS += ../src/AdItem.h
HEADERS += ../src/BRenderSDL.h
HEADERS += ../src/AdPathPoint.h
HEADERS += ../src/AdScene.h
HEADERS += ../src/BFontBitmap.h

SOURCES += ../src/UITiledImage.cpp
SOURCES += ../src/BFontTT.cpp
SOURCES += ../src/VidTheoraPlayer.cpp
SOURCES += ../src/AdScaleLevel.cpp
SOURCES += ../src/PartParticle.cpp
SOURCES += ../src/BStringTable.cpp
SOURCES += ../src/BScriptable.cpp
SOURCES += ../src/tinyxml.cpp
SOURCES += ../src/AdSentence.cpp
SOURCES += ../src/PartForce.cpp
SOURCES += ../src/BNamedObject.cpp
SOURCES += ../src/VidManager.cpp
SOURCES += ../src/SXMath.cpp
SOURCES += ../src/AdResponse.cpp
SOURCES += ../src/BSaveThumbFile.cpp
SOURCES += ../src/SysInstance.cpp
SOURCES += ../src/BFileEntry.cpp
SOURCES += ../src/PathUtil.cpp
SOURCES += ../src/AdItem.cpp
SOURCES += ../src/BDebugger.cpp
SOURCES += ../src/SXStore.cpp
SOURCES += ../src/UIText.cpp
SOURCES += ../src/AdScene.cpp
SOURCES += ../src/BPackage.cpp
SOURCES += ../src/BSaveThumbHelper.cpp
SOURCES += ../src/UIEntity.cpp
SOURCES += ../src/BGame.cpp
SOURCES += ../src/Matrix4.cpp
SOURCES += ../src/BFrame.cpp
SOURCES += ../src/BRegistry.cpp
SOURCES += ../src/SXString.cpp
SOURCES += ../src/AdSceneNode.cpp
SOURCES += ../src/UIButton.cpp
SOURCES += ../src/UIEdit.cpp
SOURCES += ../src/BDynBuffer.cpp
SOURCES += ../src/AdEntity.cpp
SOURCES += ../src/AdWaypointGroup.cpp
SOURCES += ../src/utils.cpp
SOURCES += ../src/ScValue.cpp
SOURCES += ../src/ScScript.cpp
SOURCES += ../src/AdSpriteSet.cpp
SOURCES += ../src/UIObject.cpp
SOURCES += ../src/BSurfaceSDL.cpp
SOURCES += ../src/AdTalkHolder.cpp
SOURCES += ../src/crc.cpp
SOURCES += ../src/AdLayer.cpp
SOURCES += ../src/SdlUtil.cpp
SOURCES += ../src/BActiveRect.cpp
SOURCES += ../src/BViewport.cpp
SOURCES += ../src/AdRegion.cpp
SOURCES += ../src/BTransitionMgr.cpp
SOURCES += ../src/BObject.cpp
SOURCES += ../src/SXArray.cpp
SOURCES += ../src/AdPathPoint.cpp
SOURCES += ../src/BResourceFile.cpp
SOURCES += ../src/BRenderSDL.cpp
SOURCES += ../src/AdObject.cpp
SOURCES += ../src/AdGame.cpp
SOURCES += ../src/AdPath.cpp
SOURCES += ../src/PartEmitter.cpp
SOURCES += ../src/AdSceneState.cpp
SOURCES += ../src/AdInventory.cpp
SOURCES += ../src/AdResponseBox.cpp
SOURCES += ../src/BKeyboardState.cpp
SOURCES += ../src/BQuickMsg.cpp
SOURCES += ../src/AdActor.cpp
SOURCES += ../src/BFontStorage.cpp
SOURCES += ../src/SXDate.cpp
SOURCES += ../src/BBase.cpp
SOURCES += ../src/BFont.cpp
SOURCES += ../src/tinyxmlerror.cpp
SOURCES += ../src/BSoundMgr.cpp
SOURCES += ../src/main.cpp
SOURCES += ../src/BFile.cpp
SOURCES += ../src/BParser.cpp
SOURCES += ../src/AdResponseContext.cpp
SOURCES += ../src/UIWindow.cpp
SOURCES += ../src/BSubFrame.cpp
SOURCES += ../src/ScStack.cpp
SOURCES += ../src/AdRotLevel.cpp
SOURCES += ../src/AdActorDir.cpp
SOURCES += ../src/BSound.cpp
SOURCES += ../src/BFileManager.cpp
SOURCES += ../src/AdTalkDef.cpp
SOURCES += ../src/BPkgFile.cpp
SOURCES += ../src/SXMemBuffer.cpp
SOURCES += ../src/BRenderer.cpp
SOURCES += ../src/SxObject.cpp
SOURCES += ../src/BSoundBuffer.cpp
SOURCES += ../src/tinyxmlparser.cpp
SOURCES += ../src/BDiskFile.cpp
SOURCES += ../src/PlatformSDL.cpp
SOURCES += ../src/BFontBitmap.cpp
SOURCES += ../src/AdInventoryBox.cpp
SOURCES += ../src/StringUtil.cpp
SOURCES += ../src/MathUtil.cpp
SOURCES += ../src/SXFile.cpp
SOURCES += ../src/Vector2.cpp
SOURCES += ../src/BImage.cpp
SOURCES += ../src/VidDataSource.cpp
SOURCES += ../src/AdNodeState.cpp
SOURCES += ../src/BFader.cpp
SOURCES += ../src/BSurfaceStorage.cpp
SOURCES += ../src/SysClassRegistry.cpp
SOURCES += ../src/SysClass.cpp
SOURCES += ../src/BSurface.cpp
SOURCES += ../src/ScEngine.cpp
SOURCES += ../src/BPoint.cpp
SOURCES += ../src/AdTalkNode.cpp
SOURCES += ../src/BResources.cpp
SOURCES += ../src/BRegion.cpp
SOURCES += ../src/BScriptHolder.cpp
SOURCES += ../src/FontGlyphCache.cpp
SOURCES += ../src/BSprite.cpp
SOURCES += ../src/BEvent.cpp
SOURCES += ../src/BPersistMgr.cpp

SOURCES += ../src/ConvertUTF.c
SOURCES += ../src/DirectoryOperations.c
SOURCES += ../src/FileOperations.c