#ifndef SPARSESET_H
#define SPARSESET_H
#include <span>
#include <vector>

#include "componenttable.h"
#include "typeidgenerator.h"
namespace mini {
constexpr inline quint32 INVALID_ENTITY_ID = std::numeric_limits<quint32>::max();
constexpr inline quint32 INVALID_VERSION = std::numeric_limits<quint32>::max();

struct ComponentHandle {
    uint32_t typeID;
    uint32_t entity;
    uint32_t componentByteSize;
    uint32_t version;
};

class SparseSet {
public:
    SparseSet() = default;

    template <typename Component>
    void init(quint32 expectedNumberOfComponents,
        quint32 expectedNumberOfEntities, quint32 numberOfEntities = 0)
    {
        componentTable.init<Component>(expectedNumberOfComponents);
        sparseList.reserve(expectedNumberOfEntities);
        denseList.reserve(expectedNumberOfComponents);
        versions.reserve(expectedNumberOfComponents);
        sparseList.assign(numberOfEntities, INVALID_ENTITY_ID);
    }

    bool addEmptyEntity(quint32 ntityID)
    {
        if (sparseList.size() != ntityID) {
            return false;
        }
        sparseList.push_back(INVALID_ENTITY_ID);
        return true;
    }

    /**
     * @brief Assign a component to the given entity. The entity can not have a
     * previously assigned Component of the same type.
     * @tparam ...Args Type of the constructor arguments
     * @tparam Component
     * @param entity Id of the entity
     * @param ...args Constructor arguments of the given Component Type
     */

    template <typename Component, typename... Args>
        requires std::is_constructible_v<Component, Args...>
    void emplace(quint32 entity, Args&&... args)
    {
        Q_ASSERT(sparseList[entity] == INVALID_ENTITY_ID);
        Q_ASSERT(entity < sparseList.size());
        denseList.emplace_back(entity);
        versions.emplace_back(0);
        sparseList[entity] = static_cast<quint32>(denseList.size() - 1);
        componentTable.emplace_back<Component, Args...>(
            std::forward<Args>(args)...);
    }

    /**
     * @brief Assign a component to the given entity. The entity can not have a
     * previously assigned Component of the same type.
     * @tparam Component Type of the component
     * @param entity Id of the entity
     * @param component Component to be assigned
     */
    template <typename Component>
        requires std::is_move_constructible_v<Component>
    void emplace(quint32 entity, Component&& component)
    {
        Q_ASSERT(sparseList[entity] == INVALID_ENTITY_ID);
        Q_ASSERT(entity < sparseList.size());
        denseList.emplace_back(entity);
        versions.emplace_back(0);
        sparseList[entity] = static_cast<quint32>(denseList.size() - 1);
        componentTable.emplace_back<Component>(std::forward<Component>(component));
    }

    /**
     * @brief Assign a component to the given entity.
     * @tparam Component Type of the component
     * @param entity Id of the entity
     * @param component Component to be assigned. This component will be copied
     * and has to be copy assignable.
     */
    template <typename Component>
        requires std::is_copy_assignable_v<Component>
    void emplace(quint32 entity, Component& component)
    {
        Q_ASSERT(sparseList[entity] == INVALID_ENTITY_ID);
        Q_ASSERT(entity < sparseList.size());
        denseList.emplace_back(entity);
        versions.emplace_back(0);
        sparseList[entity] = static_cast<quint32>(denseList.size() - 1);
        componentTable.emplace_back<Component>(component);
    }

    /**
     * @brief
     * @return The number of assigned components
     */
    quint32 size() const { return static_cast<quint32>(denseList.size()); }

    /**
     * @brief Check whether there exist a component for the given entity
     * @param entityID
     * @return
     */
    bool hasEntity(quint32 entityID) const
    {
        return entityID < sparseList.size() && sparseList[entityID] != INVALID_ENTITY_ID;
    }

    /**
     * @brief Remove all components from the sparse set.
     */
    void clearComponents()
    {
        for (const quint32 entity : denseList) {
            sparseList[entity] = INVALID_ENTITY_ID;
        }
        denseList.clear();
        versions.clear();
        componentTable.clear();
    }

    /**
     * @brief Deletes an entity including its component from the sparse set.
     * The to be deleted entity is swapped with the last element from the dense
     * list. Then the last index is removed.
     * @param entityID entity to be deleted
     */
    void deleteEntity(quint32 entityID)
    {
        if (sparseList[entityID] == INVALID_ENTITY_ID)
            return;

        const quint32 toDeleteEntity = sparseList[entityID];
        const quint32 lastElementIndex = denseList[denseList.size() - 1];
        const quint32 lastElementVersions = versions[versions.size() - 1];

        componentTable.swapAndDelete(toDeleteEntity);

        // Swap sparse list indices so that the delete points to an invalid entity
        // and the last points to the swapped spot
        sparseList[lastElementIndex] = toDeleteEntity;
        sparseList[entityID] = INVALID_ENTITY_ID;

        denseList[toDeleteEntity] = lastElementIndex;
        denseList.pop_back();
        versions[toDeleteEntity] = lastElementVersions;
        versions.pop_back();
    }

    /**
     * @brief Retrieves a pointer to the Component of the given type and entity in
     * memory.
     * @tparam Component
     * @param entity
     * @return The pointer of the component assigned to the entity or nullptr if
     * no component is assigned
     */
    template <typename Component>
    Component* get(quint32 entity) const
    {
        const quint32 denseListIndex = sparseList[entity];
        return denseListIndex < denseList.size()
            ? componentTable.getComponent<Component>(sparseList[entity])
            : nullptr;
    }

    /**
     * @brief Return a Component Handle for storage of components. Use
     * getFromComponentHandle to retrieve the associated component of a handle.
     * @tparam Component Component type
     * @param entity
     * @return A component handle containing the type, entity and current version
     * of a component
     */
    template <typename Component>
    ComponentHandle getComponentHandle(quint32 entity) const
    {
        const quint32 denseListIndex = sparseList[entity];
        const quint32 version = denseListIndex < denseList.size()
            ? versions[denseListIndex]
            : INVALID_VERSION;
        return ComponentHandle(TypeIDGenerator::type<Component>(), entity,
            sizeof(Component), version);
    }

    /**
     * @brief Get the associated Component from a ComponentHandle. Asserts that
     * the Component parameter matches the ComponentHandle type.
     * @tparam Component
     * @param handle
     * @return Return the associated Component or nullptr if version does not
     * match or entity is invalid
     */
    template <typename Component>
    Component* getFromComponentHandle(const ComponentHandle& handle)
    {
        Q_ASSERT(TypeIDGenerator::type<Component>() == handle.typeID);
        const quint32 denseListIndex = sparseList[handle.entity];
        const bool validHandle = denseListIndex < denseList.size() || handle.version != versions[denseListIndex];
        return validHandle ? componentTable.getComponent<Component>(
                                 sparseList[handle.entity])
                           : nullptr;
    }

    /**
     * @brief Returns a pointer to the component data at the specified byte
     * offset.
     * @param offset The offset in bytes from the start of the component data.
     * @return A const void pointer to the data at the given offset.
     *
     * @note The caller is responsible for knowing the type and bounds of the
     * data.
     */
    const void* getRawComponentData(const ComponentHandle& handle)
    {
        const quint32 denseListIndex = sparseList[handle.entity];
        const bool validHandle = denseListIndex < denseList.size() || handle.version != versions[denseListIndex];
        const size_t offset = static_cast<size_t>(denseListIndex) * handle.componentByteSize;
        return validHandle ? componentTable.getVoidPtr(offset) : nullptr;
    }

    /**
    @brief Applies a function to each component of the specified type.
     * @tparam Component The type of the component to operate on.
     * @tparam Func A callable type that takes a Component* as its argument.
     * @param func A callable that will be invoked for each component.
     */
    template <typename Component, typename Func>
    void each(Func&& func)
    {
        for (quint32 i = 0; i < denseList.size(); ++i) {
            Component* const component = componentTable.getComponent<Component>(i);
            func(component);
        }
    }

    /**
     * @brief
     * @return Span of the dense component list
     */
    std::span<const quint32> getDenseList() const
    {
        return std::span<const quint32>(denseList);
    }

private:
    std::vector<quint32> sparseList;
    std::vector<quint32> denseList;
    ComponentTable componentTable;
    std::vector<quint32> versions;
};
} // namespace mini
#endif
