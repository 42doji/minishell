#include "minishell.h"

static int	handle_lexer_and_quote(t_minishell *mini)
{
	lexer(mini);
	if (check_unfinished_quote(mini->input) == 1)
	{
		free_all(mini);
		return (0); // 오류 발생 시 종료
	}
	return (1);
}

static int	handle_tokenization(t_minishell *mini)
{
	replace_env_var(mini);
	tokenizer(mini);
	if (has_syntax_error(mini->token) == 1)
	{
		free_all(mini);
		return (0); // 오류 발생 시 종료
	}
	return (1);
}

void	initialize_shell(t_minishell *mini)
{
	mini->flag2 = 0;
	mini->error = 0;

	if (mini->str)
		add_history(mini->str);

	if (!handle_lexer_and_quote(mini)) // 어휘 분석과 인용부 검사
		return;

	if (!handle_tokenization(mini)) // 환경 변수 대체와 토큰화
		return;

	parse_command(mini, mini->token);
	execution(mini); // 명령 실행
	free_all(mini);
}
