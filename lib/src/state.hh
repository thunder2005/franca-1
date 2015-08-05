/******************************************************************************
 *                                                                            *
 * This file is a part of GeNa project / Franca IDL.                          *
 *                                                                            *
 ******************************************************************************/

#pragma once

// std includes:
#include <memory>

namespace franca {

class stm_t;
class log_t;
class input_line_t;
class input_context_t;
class ast_t;

#define DECL_PARSER_STATE_CTR(__class)                                         \
    public:                                                                    \
        __class( stm_t &stm ): state_t(#__class, stm) {}

#define DECL_PARSER_SUBSTATES(__subst1, ...)                                   \
    private:                                                                   \
        enum class subst_t {                                                   \
            __subst1, ##__VA_ARGS__                                            \
        };                                                                     \
        subst_t m_subst = subst_t::__subst1;

/*!
 * \brief Parser state.
 *
 * This is a base class for all parser's states.
 */
class state_t
{
public:
    /*!
     * \brief Get a name of this state.
     * \return Name of the state.
     */
    const char *name() const noexcept { return m_name; }

    void handle_token( input_line_t &input );
    virtual void handle_eof();

public:
    virtual ~state_t() = default;
    state_t( const state_t & ) = delete;
    state_t &operator=( const state_t & ) = delete;

protected:
    state_t( const char *name, stm_t &stm );
    virtual void goto_next_token();
    virtual void handle_token();

protected:
    ast_t &ast();

protected:
    input_context_t input_context() noexcept;
    log_t debug();
    log_t info();
    log_t warn();
    log_t error();

protected:
    template<typename T>
    void transit() noexcept
    {
        transit(std::make_shared<T>(m_stm));
    }

    template<typename T>
    void enter_substate() noexcept
    {
        enter_substate(std::make_shared<T>(m_stm));
    }

    void leave_state() noexcept;

protected:
    void raise_not_implemented( const char *feature_id = nullptr ) const;
    void raise_unexpected_eof( const char *what_expected ) const;
    void raise_type_exists( const char *tname ) const;
    void raise_type_not_found( const char *tname ) const;

protected:
    const char *m_input;

private:
    void transit( const std::shared_ptr<state_t> &new_state ) noexcept;
    void enter_substate( const std::shared_ptr<state_t> &new_state ) noexcept;

private:
    const char *m_name;
    stm_t &m_stm;
    bool m_transition_occurred;
};

} // namespace franca
