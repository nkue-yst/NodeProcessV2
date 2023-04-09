/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/09
 * Edited:  2023/04/09
 **********/

#include <cstdint>
#include <set>

class PinManager
{
public:
    PinManager();
    ~PinManager();

    uint32_t usePin();
    void unusePin(uint32_t id);

private:
    std::set<uint32_t> m_used_id;
};
