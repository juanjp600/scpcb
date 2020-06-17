#include "CollisionDefinitions.h"
#include "../../Collision/CollisionMeshCollection.h"
#include <vector>
#include "../AngelScriptAddons/scriptarray/scriptarray.h"

CollisionMesh* CollisionDefinitions::collisionMeshFactory(CScriptArray* verts, CScriptArray* inds) {
    void* e = this;
    std::vector<PGE::Vector3f> vecVerts;
    std::vector<int> vecInds;
    for (int i=0;i<verts->GetSize();i++) {
        vecVerts.push_back(*((PGE::Vector3f*)verts->At(i)));
    }
    for (int i=0;i<inds->GetSize();i++) {
        vecInds.push_back(*((int*)inds->At(i)));
    }
    CollisionMesh* newMesh = new CollisionMesh(vecVerts, vecInds);
    refCount.emplace(newMesh, 1);
    return newMesh;
}

void CollisionDefinitions::collisionMeshAddRef(CollisionMesh* mesh) {
    refCount[mesh]++;
}

void CollisionDefinitions::collisionMeshRelease(CollisionMesh* mesh) {
    refCount[mesh]--;

    if (refCount[mesh] <= 0) { refCount.erase(mesh); delete mesh; }
}

CollisionDefinitions::CollisionDefinitions(ScriptManager* mgr) {
    engine = mgr->getAngelScriptEngine();

    engine->RegisterObjectType("CollisionMesh", sizeof(CollisionMesh), asOBJ_REF);
    engine->RegisterObjectBehaviour("CollisionMesh", asBEHAVE_FACTORY, "CollisionMesh@ f(const array<Vector3f>&in verts, const array<int>&in inds)",
                                    asMETHOD(CollisionDefinitions, collisionMeshFactory), asCALL_THISCALL_ASGLOBAL, this);
    engine->RegisterObjectBehaviour("CollisionMesh", asBEHAVE_ADDREF, "void f()", asMETHOD(CollisionDefinitions,collisionMeshAddRef), asCALL_THISCALL_OBJLAST, this);
    engine->RegisterObjectBehaviour("CollisionMesh", asBEHAVE_RELEASE, "void f()", asMETHOD(CollisionDefinitions,collisionMeshRelease), asCALL_THISCALL_OBJLAST, this);
}