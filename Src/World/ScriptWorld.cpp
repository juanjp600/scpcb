#include <Misc/FileUtil.h>

#include "ScriptWorld.h"

#include "../Save/Config.h"

#include "../Scripting/ScriptManager.h"
#include "../Scripting/ScriptModule.h"
#include "../Scripting/Script.h"
#include "../Scripting/ScriptFunction.h"
#include "../Scripting/ScriptClass.h"

#include "../Scripting/NativeDefinitions/InputDefinitions.h"
#include "../Scripting/NativeDefinitions/RefCounter.h"
#include "../Scripting/NativeDefinitions/MathDefinitions.h"
#include "../Scripting/NativeDefinitions/RM2Definitions.h"
#include "../Scripting/NativeDefinitions/CollisionDefinitions.h"
#include "../Scripting/NativeDefinitions/PlayerControllerDefinitions.h"
#include "../Scripting/NativeDefinitions/EventDefinition.h"

ScriptWorld::ScriptWorld(GraphicsResources* gfxRes, Camera* camera, KeyBinds* keyBinds, const Config* config, float timestep) {
    manager = new ScriptManager();

    refCounterManager = new RefCounterManager();

    inputDefinitions = new InputDefinitions(manager, keyBinds);
    mathDefinitions = new MathDefinitions(manager);
    collisionDefinitions = new CollisionDefinitions(manager, refCounterManager);
    rm2Definitions = new RM2Definitions(manager, gfxRes);
    playerControllerDefinitions = new PlayerControllerDefinitions(manager, refCounterManager, camera);

    ScriptFunction::Signature perTickSignature;
    perTickSignature.functionName = "PerTick";
    perTickSignature.returnType = Type::Void;
    perTickSignature.arguments.push_back(ScriptFunction::Signature::Argument(Type::Float, "deltaTime"));

    perTickEventDefinition = new EventDefinition(manager, "PerTick", perTickSignature);
    perTickEventDefinition->setArgument("deltaTime", timestep);

    ScriptFunction::Signature perFrameSignature;
    perFrameSignature.functionName = "PerFrame";
    perFrameSignature.returnType = Type::Void;
    perFrameSignature.arguments.push_back(ScriptFunction::Signature::Argument(Type::Float, "interpolation"));

    perFrameEventDefinition = new EventDefinition(manager, "PerFrame", perFrameSignature);
    perFrameEventDefinition->setArgument("interpolation", 1.0f);

    const std::vector<PGE::String>& enabledMods = config->getEnabledMods();

    tinyxml2::XMLDocument doc;

    for (int i = 0; i < enabledMods.size(); i++) {
        PGE::FilePath directory = PGE::FilePath::fromStr(enabledMods[i] + "/");
        PGE::FilePath depsFile = PGE::FilePath(directory, "dependencies.cfg");
        if (PGE::FileUtil::exists(depsFile)) {
            std::vector<PGE::String> depNames = PGE::FileUtil::readLines(depsFile);
            int depsNotEnabled = (int)depNames.size();
            for (int j = 0; j < i; j++) {
                for (int k = 0; k < depNames.size(); k++) {
                    if (enabledMods[j].equals(depNames[k])) {
                        depsNotEnabled--;
                        break;
                    }
                }
            }
            if (depsNotEnabled > 0) {
                throw std::runtime_error((enabledMods[i] + " has dependencies that are not enabled before it").cstr());
            }
        }
        ScriptModule* scriptModule = new ScriptModule(manager, enabledMods[i]);
        std::vector<PGE::FilePath> files = PGE::FileUtil::enumerateFiles(directory);
        for (int j = 0; j < files.size(); j++) {
            if (files[j].getExtension().equals("as")) {
                Script* script = new Script(files[j]);
                scriptModule->addScript(files[j].str()
                    .replace("/", "")
                    .replace(".", ""), script);
            }
        }
        scriptModule->build();
        modules.push_back(scriptModule);

        ScriptFunction* mainFunction = scriptModule->getFunctionByName("main");
        if (mainFunction != nullptr) {
            mainFunction->execute();
        }

        //scriptModule->save(doc);
        //doc.LoadFile("juanIsntReal.xml");
        //scriptModule->load(doc.FirstChildElement());
        scriptModule->save(doc);
    }

    doc.SaveFile("juanIsntReal.xml");
}

ScriptWorld::~ScriptWorld() {
    for (int i = 0; i < (int)modules.size(); i++) {
        delete modules[i];
    }

    delete perTickEventDefinition;
    delete perFrameEventDefinition;

    delete inputDefinitions;
    delete mathDefinitions;
    delete rm2Definitions;
    delete collisionDefinitions;
    delete playerControllerDefinitions;

    delete refCounterManager;

    delete manager;
}

void ScriptWorld::update() {
    perTickEventDefinition->execute();
}

void ScriptWorld::draw(float interpolation) {
    perFrameEventDefinition->setArgument("interpolation", interpolation);

    perFrameEventDefinition->execute();
}