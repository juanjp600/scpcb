shared Inventory@ inventory = Inventory(10);

shared class Inventory {
    private array<InvSlot@> slots;

    Inventory(int size) {
        const int rows = Math::ceil(size / 6.0);
        if (size % rows != 0) {
            // throw("Invalid inventory size"); // TODO
        }
        const int itemsPerRow = size / rows;

        slots = array<InvSlot@>(size);

        float screenX; float screenY = -(rows * 2 - 1) * InvSlot::screenSize / 2;
        for (int y = 0; y < rows; y++) {
            screenX = -(itemsPerRow * 2 - 1) * InvSlot::screenSize / 2;
            for (int x = 0; x < itemsPerRow; x++) {
                @slots[x + y * itemsPerRow] = InvSlot(screenX, screenY);
                screenX += InvSlot::screenSize * 2;
            }
            screenY += InvSlot::screenSize * 2;
        }
    }

    bool addItem(Item@ it) {
        for (int i = 0; i < slots.length(); i++) {
            if (!slots[i].hasItem()) {
                slots[i].setItem(it);
                return true;
            }
        }
        return false;
    }

    void update(const Vector2f&in mousePos, const Vector2f&in mouseWheelDelta) {
        for (int i = 0; i < slots.length(); i++) {
            slots[i].update(mousePos);
        }
    }

    void render() {
        for (int i = 0; i < slots.length(); i++) {
            slots[i].render();
        }
    }
}