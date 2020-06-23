serialize EntranceZone@ entranceZone;

// TODO: remove these globals, they only exist for testing purposes
serialize Vector3f whVy = Vector3f(17, 14, 14);
serialize string uh = "aaah";
serialize Matrix4x4f worldMatrix = Matrix4x4f::constructWorldMat(Vector3f(0, 0, 0), Vector3f(1, 1, 1), Vector3f(0, 0, 0));

PlayerController@ testController;
Collision::Collection@ testCollCollection;

external shared enum RoomType;

void main() {
    @entranceZone = EntranceZone();
    @testCollCollection = Collision::Collection();
    @testController = PlayerController(1.0, 3.0);
    testController.setPosition(Vector3f(0,3,0));
    testController.setCollisionCollection(testCollCollection);
    entranceZone.registerRoom("hll_plain_4", Room4, hll_plain_4::construct);
    entranceZone.generate();
    PerTick::register(update);
    PerFrame::register(render);
}

void update(float deltaTime) {
    __UPDATE_PLAYERCONTROLLER_TEST_TODO_REMOVE(testController);
}

void render(float interpolation) {
    entranceZone.render(interpolation);
}