#ifndef COMPONENTVIEW_H
#define COMPONENTVIEW_H
#include "sparseset.h"
#include "typeidgenerator.h"
#include <array>
#include <span>

namespace mini {
/**
 * @brief The component table serves as view allowing to iterate over entities
 * with a specific set of components.
 * @tparam ...Components The type of components all iterated entities need to
 * have.
 */
template <typename... Components>
class ComponentView {
public:
    explicit ComponentView(
        std::array<const SparseSet*, sizeof...(Components)> sets)
        : sparseSets(sets)
    {
        quint32 size = sparseSets[0]->size();
        for (quint32 i = 1; i < sparseSets.size(); i++) {
            if (size < sparseSets[i]->size()) {
                size = sparseSets[i]->size();
                smallestSet = i;
            }
        }
    }

    /**
     * @brief Iterator for a Component View. It traverses through the smallest
     * denseList of all components. Entities with no component of the specified
     * type will be skipped.
     * @tparam numberOfComponents
     */
    template <quint32 numberOfComponents>
    struct ComponentIterator {
        ComponentIterator(
            std::array<const SparseSet*, numberOfComponents>* viewSets,
            quint32 smallestIndex, std::span<const quint32>::iterator iterator)
            : sparseSets(viewSets)
            , smallestSparseSetIndex(smallestIndex)
            , current(iterator)
        {
        }

        /**
         * @brief Advances the iterator to the next valid entity.
         * @return The current position of the Iterator
         */
        ComponentIterator<numberOfComponents>& operator++()
        {
            do {
                current++;
            } while (
                current != (*sparseSets)[smallestSparseSetIndex]->getDenseList().end() && valid(*current));
            return *this;
        }

        /**
         * @brief Checks wether an entity has a valid component for all component
         * types of the view.
         * @param entityID Id of the entity
         * @return true if the entity has valid components
         */
        bool valid(quint32 entityID)
        {
            for (quint32 i = 0; i < sparseSets->size(); i++) {
                if (!(*sparseSets)[i]->hasEntity(entityID)) {
                    return false;
                }
            }
            return true;
        }

        quint32 operator*() const { return *current; }
        bool operator!=(const ComponentIterator& other) const
        {
            return current != other.current;
        }

        const quint32 smallestSparseSetIndex;
        std::span<const quint32>::iterator current;
        std::array<const SparseSet*, numberOfComponents>* sparseSets { nullptr };
    };

    /**
     * @brief Returns an iterator to the first valid entity with all specified
     * components.
     * @return A ComponentIterator pointing to the first valid matching entity.
     */
    ComponentIterator<sizeof...(Components)> begin()
    {
        std::span<const quint32>::iterator it = sparseSets[smallestSet]->getDenseList().begin();
        while (*it == std::numeric_limits<quint32>::max()) {
            it++;
        }
        return ComponentIterator<sizeof...(Components)>(&sparseSets, smallestSet,
            it);
    }

    /**
     * @brief Retrieves a pointer to the component of a given entity.
     * @tparam Component The type of the component
     * @param entityID The ID of the entity whose component is to be retrieved.
     * @return  pointer to the component of the specified entity, or nullptr if
     * not found.
     */
    template <typename Component>
    Component* get(quint32 entityID) const
    {
        const quint32 typeIndex = mini::TypeIDGenerator::type<Component>();
        Q_ASSERT(typeIndex < sparseSets.size());
        return sparseSets[typeIndex].template get<Component>(entityID);
    }

    /**
     * @brief Returns an iterator pointing past the last valid entity.
     * @return
     */
    ComponentIterator<sizeof...(Components)> end()
    {
        return ComponentIterator<sizeof...(Components)>(
            &sparseSets, smallestSet,
            sparseSets[smallestSet]->getDenseList().end());
    }

private:
    quint32 smallestSet { 0 };
    std::array<const SparseSet*, sizeof...(Components)> sparseSets;
};
} // namespace mini
#endif
